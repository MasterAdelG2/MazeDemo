// Copyright Epic Games, Inc. All Rights Reserved.

#include "MazePlayerCharacter.h"
#include "Pickable.h"
#include "Objective.h"
#include "MazeBFL.h"
#include "MazeGS.h"
#include "MazePC.h"
#include "MazeHUD.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// MazePlayerCharacter

AMazePlayerCharacter::AMazePlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Inventory Component
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	InventoryComponent->SetIsReplicated(true);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh(TEXT("SkeletalMesh'/Game/Models/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple'"));
	GetMesh()->SetSkeletalMesh(CharacterMesh.Object);


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AMazePlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	//
	if (!UKismetSystemLibrary::IsDedicatedServer(this))
	{
		SetCharacterColor();
		UWorld* World = GetWorld();
		if (ensure(World))
		{
			FTimerHandle THandle;
			World->GetTimerManager().SetTimer(
				THandle,
				this,
				&AMazePlayerCharacter::UpdateObjectiveMeterValue,
				UpdateObjectiveMeterInterval,
				true);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMazePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMazePlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMazePlayerCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMazePlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMazePlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMazePlayerCharacter::Pickup_Implementation(APickable* PickableRef)
{
	if (ensure(PickableRef))
	{
		InventoryComponent->AddItem(PickableRef->ItemData);
		AMazeGS* MazeGS = UMazeBFL::GetMazeGS(this);
		AController* PawnController = GetController();
		AObjective* objective = Cast<AObjective>(PickableRef);
		if (ensure(objective) && 
			ensure(MazeGS) && 
			ensure(PawnController))
		{
			APlayerController* PC = Cast<APlayerController>(PawnController);
			if (ensure(PC))
			{
				MazeGS->OnObjectivePickup(objective, PC);
			}
		}
	}
}

void AMazePlayerCharacter::UpdateObjectiveMeterValue_Implementation()
{
	AMazePC* MazePC = UMazeBFL::GetMazePC(this);
	if (ensure(MazePC))
	{
		AMazeHUD* MazeHUD = MazePC->GetHUD<AMazeHUD>();
		if (ensure(MazeHUD))
		{
			MazeHUD->SetMeter(GetNearestObjectiveDistance());
		}
	}
}

int32 AMazePlayerCharacter::GetNearestObjectiveDistance_Implementation()
{
	int32 result = 0;
	float MinimumDistance = 5000.f;
	AMazeGS* MazeGS = UMazeBFL::GetMazeGS(this);
	if (ensure(MazeGS))
	{
		TArray<AObjective*> AllObjectives = MazeGS->SpawnedObjectives;
		for (AObjective* obj : AllObjectives)
		{
			if (ensure(obj))
			{
				float ObjDistance = FVector::Distance(GetActorLocation(), obj->GetActorLocation());
				if (ObjDistance < MinimumDistance)
				{
					MinimumDistance = ObjDistance;
				}
			}
		}
		result = FMath::Max(0, 100.f - (MinimumDistance / 50.f));
	}
	return result;
}