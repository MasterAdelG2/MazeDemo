// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MazePC.generated.h"

/**
 * 
 */
UCLASS()
class MAZEDEMO_API AMazePC : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMazePC();

	// Spawns The Default Maze Character Assigned or Spectator if chose no team
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Maze Player Controller")
	void SpawnPlayerPawn();
	// Gets The Spawn Transform for the pawn by the player team
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure, Category = "Maze Player Controller")
	FTransform GetSpawnTransform(ETeam PlayerTeam);
	// Gets the Spawn Point Tag by the player Team
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure, Category = "Maze Player Controller")
	FString GetSpawnTag(ETeam PlayerTeam);
	// Gets The Pawn Class to be spawned
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure, Category = "Maze Player Controller")
	TSubclassOf<APawn> GetSpawnClass(ETeam PlayerTeam);
	// Shows the maze game screen & enables game input
	UFUNCTION(BlueprintCallable, Client, reliable, Category = "Maze Player Controller")
	void OC_OnStartGame();
	// Shows the end game screen & disables game input
	UFUNCTION(BlueprintCallable, Client, reliable, Category = "Maze Player Controller")
	void OC_OnEndGame();

	// The Default Maze Characer Class that player will posses if not spectator
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Maze Player Controller")
	TSubclassOf<APawn> DefaultMazeCharacter = nullptr;

};
