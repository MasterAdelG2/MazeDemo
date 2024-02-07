// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DevomonDemo.h"
#include "MazeGS.generated.h"

/**
 * 
 */
UCLASS()
class DEVOMONDEMO_API AMazeGS : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	// Adds Score to the Picking Team and Checks If the Game Ended
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Maze Game State")
	void OnObjectivePickup(class AObjective* Objective, class APlayerController* PlayerController);
	// Checks if there are any more objectives in the maze
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Maze Game State")
	void CheckGameEnd();
	// Gets The Winner Team or Spectator if Draw
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure, Category = "Maze Game State")
	ETeam GetWinnerTeam();

	// Number of Objectives Collected by Team A
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Maze Game State")
	int32 TeamAScore = 0;
	// Number of Objectives Collected by Team B
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Maze Game State")
	int32 TeamBScore = 0;
	// All Spawned Objectives Refrence
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Maze Game State")
	TArray<class AObjective*> SpawnedObjectives;
};
