// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class MAZEDEMO_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

	// Billboard to make it easier for Level Designers to configure the maze
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Point")
	UBillboardComponent* BillboardComponent = nullptr;
};
