// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class DEVOMONDEMO_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBillboardComponent* BillboardComponent;
};
