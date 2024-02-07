// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBFL.h"
#include "Kismet/GameplayStatics.h"
#include "MazeHUD.h"
#include "MazeGM.h"
#include "MazeGS.h"
#include "MazePC.h"
#include "MazePS.h"
#include "MazePlayerCharacter.h"

AMazeGM* UMazeBFL::GetMazeGM(UObject* WorldContextObject)
{
	return Cast <AMazeGM>(UGameplayStatics::GetGameMode(WorldContextObject));
}

AMazeGS* UMazeBFL::GetMazeGS(UObject* WorldContextObject)
{
	return Cast <AMazeGS>(UGameplayStatics::GetGameState(WorldContextObject));
}

AMazePC* UMazeBFL::GetMazePC(UObject* WorldContextObject)
{
	return Cast <AMazePC>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
}

AMazePS* UMazeBFL::GetMazePS(UObject* WorldContextObject)
{
	return GetMazePC(WorldContextObject)->GetPlayerState<AMazePS>();
}

AMazeHUD* UMazeBFL::GetMazeHUD(UObject* WorldContextObject)
{
	return GetMazePC(WorldContextObject)->GetHUD<AMazeHUD>();
}

AMazePlayerCharacter* UMazeBFL::GetMazePlayerPawn(UObject* WorldContextObject)
{
	return Cast <AMazePlayerCharacter>(UGameplayStatics::GetPlayerPawn(WorldContextObject, 0));
}