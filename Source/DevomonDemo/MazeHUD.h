// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MazeHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEVOMONDEMO_API AMazeHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnJoinServer();
	//
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnStartGame();
	//
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnEndGame();
	//
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetMeter(int32 MeterValue);
	//
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateInventoryList();
};
