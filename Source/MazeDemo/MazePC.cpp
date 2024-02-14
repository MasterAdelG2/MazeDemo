// Fill out your copyright notice in the Description page of Project Settings.

#include "MazePC.h"
#include "MazeBFL.h"
#include "MazePS.h"
#include "MazeGM.h"
#include "MazeHUD.h"
#include "MazePlayerCharacter.h"
#include "GameFramework/SpectatorPawn.h"
#include "Kismet/GameplayStatics.h"

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
	AMazePS* MazePS = GetPlayerState<AMazePS>();
	if (MazePS)
	{
		FTransform SpawnTransform = GetSpawnTransform(MazePS->PlayerTeam);
		TSubclassOf<APawn> PawnClass = GetSpawnClass(MazePS->PlayerTeam);
		UWorld* World = GetWorld();
		if (World)
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
	if (MazeGM)
	{
		AActor* StartPoint = MazeGM->FindPlayerStart(this, GetSpawnTag(PlayerTeam));
		if (StartPoint)
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
	if (DefaultMazeCharacter)
	{
		return DefaultMazeCharacter;
	}
	return AMazePlayerCharacter::StaticClass();
}

void AMazePC::OC_OnStartGame_Implementation()
{
	AMazeHUD* MazeHUD = UMazeBFL::GetMazeHUD(this);
	if (MazeHUD)
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
	if (ControlledPawn)
	{
		ControlledPawn->DisableInput(this);
	}
	//
	SetShowMouseCursor(true);
	FInputModeUIOnly UIInput;
	SetInputMode(UIInput);
	//
	AMazeHUD* MazeHUD = UMazeBFL::GetMazeHUD(this);
	if (MazeHUD)
	{
		MazeHUD->OnEndGame();
	}
}