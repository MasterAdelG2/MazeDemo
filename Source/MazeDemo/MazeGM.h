// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MazeDemo.h"
#include "MazeGM.generated.h"

/**
 * 
 */
UCLASS()
class MAZEDEMO_API AMazeGM : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Sets default GameMode properties
	AMazeGM();
	// Spawns All Objectives on Available spawn Points
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Maze Game Mode")
	void SpawnObjectives();
	// Starts The Maze And Spawns The Players According to their Teams
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Maze Game Mode")
	void StartGame();
	// Checks If All Players are ready
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Maze Game Mode")
	void CheckReadyStates();
	// Ends the Game And show the Result of the Maze
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Maze Game Mode")
	void EndGame();
	// Restarts The Game
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Maze Game Mode")
	void RestartLevel();
	// Can start Game Checks for players ready states & at least 1 player assigned to team
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure, Category = "Maze Game Mode")
	bool CanStartGame();

	// Removes Player Controller from the Array
	virtual void Logout(AController* Exiting) override;
protected:
	// Adds The New Player Controller Refrence to a list for later use
	virtual void OnPostLogin(AController* NewPlayer) override;

public:
	// All Objectives Data to be spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze Game Mode")
	TArray<FItemData> ObjectivesData;
	// Number Of Spawned Objectives
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze Game Mode")
	int32 ObjectivesCount = 3;
	// All Player Controllers in the server
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze Game Mode")
	TArray<class AMazePC*> AllPCs;
	// Random Player Names Given for players in the server
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze Game Mode")
	TArray<FString> RandomPlayerNames = {TEXT("Alpha") ,TEXT("Beta"), TEXT("Charlie"), TEXT("Delta") ,TEXT("Echo"), TEXT("Foxtrot"), TEXT("Gamma"), TEXT("Hotel")};

};
