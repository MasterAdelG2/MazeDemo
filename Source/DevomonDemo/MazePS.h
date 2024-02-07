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
	// Toggles the ready state of the plauer
	UFUNCTION(BlueprintCallable, Server, reliable, Category = "Maze Player State")
	void SR_ToggleReady();
	// Changes the player Assigned Team
	UFUNCTION(BlueprintCallable, Server, reliable, Category = "Maze Player State")
	void SR_JoinTeam(ETeam NewTeam);

	// Selected Player Team
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Maze Player State")
	ETeam PlayerTeam = ETeam::Spectator;
	// Player Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Maze Player State")
	FString PlayerName = TEXT("");
	// Player's Ready State
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Maze Player State")
	bool bIsReady = false;
	
};
