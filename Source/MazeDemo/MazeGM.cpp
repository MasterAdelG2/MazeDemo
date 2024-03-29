// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGM.h"
#include "MazePC.h"
#include "MazeGS.h"
#include "MazePS.h"
#include "MazeHUD.h"
#include "MazeBFL.h"
#include "SpawnPoint.h"
#include "Engine/World.h"
#include "Objective.h"
#include "Kismet/GameplayStatics.h"

AMazeGM::AMazeGM()
{
	static ConstructorHelpers::FClassFinder<AMazeGS> MazeGSClass(TEXT("Blueprint'/Game/Blueprints/BP_MazeGS.BP_MazeGS_C'"));
	static ConstructorHelpers::FClassFinder<AMazePC> MazePCClass(TEXT("Blueprint'/Game/Blueprints/BP_MazePC.BP_MazePC_C'"));
	static ConstructorHelpers::FClassFinder<AMazePS> MazePSClass(TEXT("Blueprint'/Game/Blueprints/BP_MazePS.BP_MazePS_C'"));
	static ConstructorHelpers::FClassFinder<AMazeHUD> MazeHUDClass(TEXT("Blueprint'/Game/Blueprints/BP_MazeHUD.BP_MazeHUD_C'"));

	GameStateClass = MazeGSClass.Class;
	PlayerControllerClass = MazePCClass.Class;
	PlayerStateClass = MazePSClass.Class;
	HUDClass = MazeHUDClass.Class;
	DefaultPawnClass = NULL;
}

void AMazeGM::SpawnObjectives_Implementation()
{
	TArray<AObjective*> AllSpawnedObjectives;
	TArray<AActor*> SpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(this, ASpawnPoint::StaticClass(), SpawnPoints);
	for (int32 i = 0 ; i < ObjectivesCount ; i++)
	{
		UWorld* World = GetWorld();
		if (SpawnPoints.Num() > 0 &&
			ObjectivesData.Num() > i &&
			World)
		{
			int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num()-1);
			FTransform SpawnTransform = FTransform(SpawnPoints[RandomIndex]->GetActorLocation());
			AActor* MyDeferredActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, AObjective::StaticClass(), SpawnTransform);
			AObjective* SpawnedObjective = Cast<AObjective>(MyDeferredActor);
			SpawnedObjective->ItemData = ObjectivesData[i];
			UGameplayStatics::FinishSpawningActor(MyDeferredActor, SpawnTransform);
			AllSpawnedObjectives.AddUnique(SpawnedObjective);
			SpawnPoints.RemoveAt(RandomIndex);
		}
	}
	AMazeGS* MazeGS = UMazeBFL::GetMazeGS(this);
	if (MazeGS)
	{
		MazeGS->SpawnedObjectives = AllSpawnedObjectives;
	}
}

bool AMazeGM::CanStartGame_Implementation()
{
	bool bHasPlayerInTeam = false;
	bool AllPlayersReady = true;
	TArray<TObjectPtr<APlayerState>> AllPlayersStates = UMazeBFL::GetMazeGS(this)->PlayerArray;
	for (TObjectPtr<APlayerState> ps : AllPlayersStates)
	{
		AMazePS* MazePS = Cast<AMazePS>(ps);
		if (MazePS)
		{
			if (MazePS->bIsReady)
			{
				if (MazePS->PlayerTeam != ETeam::Spectator)
				{
					bHasPlayerInTeam = true;
				}
			}
			else
			{
				AllPlayersReady = false;
				break;
			}
		}
	}
	return bHasPlayerInTeam && AllPlayersReady;
}

void AMazeGM::StartGame_Implementation()
{
	SpawnObjectives();
	for (AMazePC* pc : AllPCs)
	{
		pc->SpawnPlayerPawn();
	}
}

void AMazeGM::CheckReadyStates_Implementation()
{
	if (CanStartGame())
	{
		// Delay 1 Sec Before Start Game
		FTimerHandle THandle;
		GetWorld()->GetTimerManager().SetTimer(
			THandle,
			this,
			&AMazeGM::StartGame,
			1.f,
			false);
	}
}

void AMazeGM::EndGame_Implementation()
{
	for (AMazePC* pc : AllPCs)
	{
		if (pc)
		{
			pc->OC_OnEndGame();
		}
	}
	// Delay 20 Sec Before Restart Game
	FTimerHandle THandle;
	GetWorld()->GetTimerManager().SetTimer(
		THandle,
		this,
		&AMazeGM::RestartLevel,
		20.f,
		false);
}

void AMazeGM::RestartLevel_Implementation()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel(TEXT("/Game/Maps/MazeMap"));
	}
}

void AMazeGM::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	//
	AMazePC* MazePC = Cast<AMazePC>(NewPlayer);
	if (MazePC)
	{
		AllPCs.AddUnique(MazePC);
		AMazePS* MazePS = MazePC->GetPlayerState<AMazePS>();
		if (MazePS)
		{
			int32 NameIndex = AllPCs.Num() - 1;
			if (NameIndex < RandomPlayerNames.Num())
			{
				MazePS->PlayerName = RandomPlayerNames[NameIndex];
			}
		}
	}
}

void AMazeGM::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	//
	AMazePC* MazePC = Cast<AMazePC>(Exiting);
	if (MazePC)
	{
		AllPCs.Remove(MazePC);
	}
}