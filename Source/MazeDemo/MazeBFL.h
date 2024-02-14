// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MazeBFL.generated.h"

/**
 * 
 */
UCLASS()
class MAZEDEMO_API UMazeBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	// Gets The Default Maze HUD Class Refrence
	UFUNCTION(BlueprintPure, Category = "Maze | Defaults", meta = (DisplayName = "Get Maze HUD", WorldContext = "WorldContextObject"))
	static UPARAM(DisplayName="MazeHUD") class AMazeHUD* GetMazeHUD(UObject * WorldContextObject);
	// Gets The Default Maze Game Mode Class Refrence
	UFUNCTION(BlueprintPure, Category = "Maze | Defaults", meta = (DisplayName = "Get Maze GM", WorldContext = "WorldContextObject"))
	static UPARAM(DisplayName = "MazeGM") class AMazeGM* GetMazeGM(UObject* WorldContextObject);
	// Gets The Default Maze Game State Class Refrence
	UFUNCTION(BlueprintPure, Category = "Maze | Defaults", meta = (DisplayName = "Get Maze GS", WorldContext = "WorldContextObject"))
	static UPARAM(DisplayName = "MazeGS") class AMazeGS* GetMazeGS(UObject* WorldContextObject);
	// Gets The Default Maze Player Controller Class Refrence
	UFUNCTION(BlueprintPure, Category = "Maze | Defaults", meta = (DisplayName = "Get Maze PC", WorldContext = "WorldContextObject"))
	static UPARAM(DisplayName = "MazePC") class AMazePC* GetMazePC(UObject* WorldContextObject);
	// Gets The Default Maze Player State Class Refrence
	UFUNCTION(BlueprintPure, Category = "Maze | Defaults", meta = (DisplayName = "Get Maze PS", WorldContext = "WorldContextObject"))
	static UPARAM(DisplayName = "MazePS") class AMazePS* GetMazePS(UObject* WorldContextObject);
	// Gets The Default Maze Player Character Class Refrence
	UFUNCTION(BlueprintPure, Category = "Maze | Defaults", meta = (DisplayName = "Get Maze Player Pawn", WorldContext = "WorldContextObject"))
	static UPARAM(DisplayName = "MazePawn") class AMazePlayerCharacter* GetMazePlayerPawn(UObject* WorldContextObject);

};
