// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeBFL.h"
#include "MazePC.h"
#include "MazePS.h"
#include "MazeGM.h"
#include "MazeHUD.h"
#include "MazePlayerCharacter.h"
#include "GameFramework/SpectatorPawn.h"

// Sets default values
AMazePC::AMazePC()
{
	SetShowMouseCursor(true);
	//
	static ConstructorHelpers::FClassFinder<AMazePlayerCharacter> PlayerPawnClass(TEXT("Blueprint'/Game/Blueprints/BP_MazePlayerCharacter.BP_MazePlayerCharacter_C'"));
	DefaultMazeCharacter = PlayerPawnClass.Class;
}
void AMazePC::SpawnPlayerPawn_Implementation()
{
	AMazePS* MazePS = UMazeBFL::GetMazePS(this);
	if (ensure(MazePS))
	{
		FTransform SpawnTransform = GetSpawnTransform(MazePS->PlayerTeam);
		TSubclassOf<APawn> PawnClass = GetSpawnClass(MazePS->PlayerTeam);
		UWorld* World = GetWorld();
		if (ensure(World))
		{
			APawn* PawnRef = World->SpawnActor<APawn>(PawnClass, SpawnTransform);
			Possess(PawnRef);
			OC_OnStartGame();
		}
	}
}

FTransform AMazePC::GetSpawnTransform_Implementation(ETeam PlayerTeam)
{
	FVector SpawnLoc = FVector();
	AMazeGM* MazeGM = UMazeBFL::GetMazeGM(this);
	if (ensure(MazeGM))
	{
		AActor* StartPoint = MazeGM->FindPlayerStart(this, GetSpawnTag(PlayerTeam));
		if (ensure(StartPoint))
		{
			SpawnLoc = StartPoint->GetActorLocation();
		}
	}
	return FTransform(SpawnLoc);
}

FString AMazePC::GetSpawnTag_Implementation(ETeam PlayerTeam)
{
	switch (PlayerTeam)
	{
	case ETeam::Spectator:
		return TEXT("Spectator");
	case ETeam::Team_A:
		return TEXT("Team A");
	case ETeam::Team_B:
		return TEXT("Team B");
	default: 
		return TEXT("");
	}
}

TSubclassOf<APawn> AMazePC::GetSpawnClass_Implementation(ETeam PlayerTeam)
{
	if (PlayerTeam == ETeam::Spectator)
	{
		return ASpectatorPawn::StaticClass();
	}
	if (ensure(DefaultMazeCharacter))
	{
		return DefaultMazeCharacter;
	}
	return AMazePlayerCharacter::StaticClass();
}

void AMazePC::OC_OnStartGame_Implementation()
{
	AMazeHUD* MazeHUD = UMazeBFL::GetMazeHUD(this);
	if (ensure(MazeHUD))
	{
		MazeHUD->OnStartGame();
	}
	SetShowMouseCursor(false);
	FInputModeGameOnly GameInput;
	SetInputMode(GameInput);
}

void AMazePC::OC_OnEndGame_Implementation()
{
	//
	APawn* ControlledPawn = GetPawn();
	if (ensure(ControlledPawn))
	{
		ControlledPawn->DisableInput(this);
	}
	//
	SetShowMouseCursor(true);
	FInputModeUIOnly UIInput;
	SetInputMode(UIInput);
	//
	AMazeHUD* MazeHUD = UMazeBFL::GetMazeHUD(this);
	if (ensure(MazeHUD))
	{
		MazeHUD->OnEndGame();
	}
}