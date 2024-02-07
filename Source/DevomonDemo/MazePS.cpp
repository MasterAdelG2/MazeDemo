// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePS.h"
#include "MazeBFL.h"
#include "MazeGM.h"
#include "Net/UnrealNetwork.h"

void AMazePS::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//
	DOREPLIFETIME(AMazePS, PlayerTeam);
	DOREPLIFETIME(AMazePS, PlayerName);
	DOREPLIFETIME(AMazePS, bIsReady);
}

void AMazePS::SR_ToggleReady_Implementation()
{
	bIsReady = !bIsReady;
	AMazeGM* MazeGM = UMazeBFL::GetMazeGM(this);
	if (ensure(MazeGM))
	{
		MazeGM->CheckReadyStates();
	}
}

void AMazePS::SR_JoinTeam_Implementation(ETeam NewTeam)
{
	PlayerTeam = NewTeam;
}