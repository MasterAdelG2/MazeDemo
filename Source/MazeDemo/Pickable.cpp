// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MazePlayerCharacter.h"
#include "Net/UnrealNetwork.h"

void APickable::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//
	DOREPLIFETIME(APickable, ItemData);
}

// Called when the game starts or when spawned
void APickable::BeginPlay()
{
	Super::BeginPlay();
	//
	SetModel();
}

// Sets default values
APickable::APickable()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	//
	// Setting Up Components
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetSphereRadius(100.f);
	RootComponent = SphereCollision;

	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	Model->SetupAttachment(SphereCollision);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APickable::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Color(TEXT("MaterialInstanceConstant'/Game/Models/Shapes/MI_Solid_Blue.MI_Solid_Blue'"));
	ColorMaterial = Color.Object;
}

void APickable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (UKismetSystemLibrary::IsDedicatedServer(this))
	{
		AMazePlayerCharacter* PlayerCharacter =Cast<AMazePlayerCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			PlayerCharacter->Pickup(this);
			Destroy();
		}
	}
}

void APickable::SetModel_Implementation()
{
	Model->SetStaticMesh(ItemData.Shape);
	if (ColorMaterial)
	{
		Model->SetMaterial(0, ColorMaterial);
	}
}