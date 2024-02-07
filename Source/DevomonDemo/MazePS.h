// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DevomonDemo.h"
#include "MazePS.generated.h"

/**
 * 
 */
UCLASS()
class DEVOMONDEMO_API AMazePS : public APlayerState
{
	GENERATED_BODY()

public:
	// Spawns All Objectives on random position
	UFUNCTION(BlueprintCallable, Server, reliable)
	void SR_ToggleReady();
	// 
	UFUNCTION(BlueprintCallable, Server, reliable)
	void SR_JoinTeam(ETeam NewTeam);

	// Selected Player Team
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Stats")
	ETeam PlayerTeam = ETeam::Spectator;
	// Player Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Stats")
	FString PlayerName = TEXT("");
	// Player's Ready State
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Stats")
	bool bIsReady = false;
	
};
