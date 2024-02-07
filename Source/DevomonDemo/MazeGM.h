// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DevomonDemo.h"
#include "MazeGM.generated.h"

/**
 * 
 */
UCLASS()
class DEVOMONDEMO_API AMazeGM : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Sets default GameMode properties
	AMazeGM();
	// Spawns All Objectives on random position
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpawnObjectives();
	// 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartGame();
	// 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CheckReadyStates();
	// 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndGame();
	// 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RestartLevel();
	// Can start Game Checks for players ready states & team assigned
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	bool CanStartGame();

	virtual void Logout(AController* Exiting) override;
protected:
	virtual void OnPostLogin(AController* NewPlayer) override;

public:
	// All Objectives Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze Configurations")
	TArray<FItemData> ObjectivesData;
	// Number Of Spawned Objectives
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze Configurations")
	int32 ObjectivesCount = 3;
	// All Player Controllers in the server
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dedicated Server")
	TArray<class AMazePC*> AllPCs;
	// Random Player Name Given for players in the server
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dedicated Server")
	TArray<FString> RandomPlayerNames = {TEXT("Alpha") ,TEXT("Beta"), TEXT("Charlie"), TEXT("Delta") ,TEXT("Echo"), TEXT("Foxtrot"), TEXT("Gamma"), TEXT("Hotel")};

};
