// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MazePC.generated.h"

/**
 * 
 */
UCLASS()
class DEVOMONDEMO_API AMazePC : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMazePC();

	// 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpawnPlayerPawn();
	//
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	FTransform GetSpawnTransform(ETeam PlayerTeam);
	// 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	FString GetSpawnTag(ETeam PlayerTeam);
	// 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	TSubclassOf<APawn> GetSpawnClass(ETeam PlayerTeam);
	// 
	UFUNCTION(BlueprintCallable, Client, reliable)
	void OC_OnStartGame();
	// 
	UFUNCTION(BlueprintCallable, Client, reliable)
	void OC_OnEndGame();

	// The Default Maze Characer Class that player will posses if not spectator
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PawnClass")
	TSubclassOf<APawn> DefaultMazeCharacter;

};
