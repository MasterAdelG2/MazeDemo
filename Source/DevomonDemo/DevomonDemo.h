// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DevomonDemo.generated.h"

// Team choices
UENUM(BlueprintType)
enum class ETeam : uint8
{
	Spectator = 0		UMETA(DisplayName = "Spectator"),
	Team_A = 1		UMETA(DisplayName = "Team A"),
	Team_B = 2		UMETA(DisplayName = "Team B"),
};

// Holds All Item Data
USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()


	// Item ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	int32 ID = 0;
	// Item Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FString Name = TEXT("");
	// Item Shape
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	class UStaticMesh* Shape;
	// Item Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =" ItemData")
	class UTexture2D* Image;
};