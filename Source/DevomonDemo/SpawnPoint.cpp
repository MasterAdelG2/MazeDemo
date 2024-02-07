// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "Components/BillboardComponent.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SetActorHiddenInGame(true);
	SetCanBeDamaged(false);

	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = BillboardComponent;
}

