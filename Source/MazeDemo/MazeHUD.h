// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MazeHUD.generated.h"

/**
 * 
 */
UCLASS()
class MAZEDEMO_API AMazeHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Shows The Deploy Screen to select Teams
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Maze HUD")
	void OnJoinServer();
	// Removes The Deploy Screen And Shows The Game Screen
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Maze HUD")
	void OnStartGame();
	// Shows The End Screen Above the Game Screen
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Maze HUD")
	void OnEndGame();
	// Updates The Meter Value on the Game Screen
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Maze HUD")
	void SetMeter(int32 MeterValue);
	// Updates The Inventory Items List on Game Screen
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Maze HUD")
	void UpdateInventoryList();
};
