// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGS.h"
#include "Objective.h"
#include "MazeBFL.h"
#include "MazeGM.h"
#include "MazePS.h"
#include "Net/UnrealNetwork.h"

void AMazeGS::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//
	DOREPLIFETIME(AMazeGS, TeamAScore);
	DOREPLIFETIME(AMazeGS, TeamBScore);
	DOREPLIFETIME(AMazeGS, SpawnedObjectives);
}

void AMazeGS::OnObjectivePickup_Implementation(AObjective* Objective, APlayerController* PlayerController)
{
	if (Objective && PlayerController)
	{
		SpawnedObjectives.Remove(Objective);
		AMazePS* MazePS = PlayerController->GetPlayerState<AMazePS>();
		if (MazePS)
		{
			if (MazePS->PlayerTeam == ETeam::Team_A)
			{
				TeamAScore++;
			}
			else if (MazePS->PlayerTeam == ETeam::Team_B)
			{
				TeamBScore++;
			}
			CheckGameEnd();
		}
	}
}

void AMazeGS::CheckGameEnd_Implementation()
{
	if (SpawnedObjectives.Num() == 0)
	{
		AMazeGM* MazeGM = UMazeBFL::GetMazeGM(this);
		if (MazeGM)
		{
			// Delay 1 Sec Before End Game
			FTimerHandle THandle;
			GetWorld()->GetTimerManager().SetTimer(
				THandle,
				MazeGM,
				&AMazeGM::EndGame,
				1.f,
				false);
		}
	}
}

ETeam AMazeGS::GetWinnerTeam_Implementation()
{
	bool IsDraw = TeamAScore == TeamBScore;
	bool WinnerA = TeamAScore > TeamBScore;
	if (IsDraw)
	{
		return ETeam::Spectator;
	}
	return WinnerA ? ETeam::Team_A : ETeam::Team_B;
}