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
	// Spawns All Objectives on random position
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnObjectivePickup(class AObjective* Objective, class APlayerController* PlayerController);
	// 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CheckGameEnd();
	// 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	ETeam GetWinnerTeam();

	// Number of Objectives Collected by Team A
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Maze Stats")
	int32 TeamAScore = 0;
	// Number of Objectives Collected by Team B
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Maze Stats")
	int32 TeamBScore = 0;
	// All Spawned Objectives Refrence
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Maze Stats")
	TArray<class AObjective*> SpawnedObjectives;
};
