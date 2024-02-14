// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MazeDemo.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAZEDEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Adds an Item to the Inventory Array
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory Component")
	void AddItem(const FItemData NewItem);

	// Replication On Owning Client to Show Inventory Change In UI & Sound
	UFUNCTION()
	void OnRep_InventoryItems();
		
	// All Inventory Items Player has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_InventoryItems, Category = "Inventory Component")
	TArray< FItemData> InventoryItems;
	// Sound Played On Picking up New Items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Component")
	class USoundBase* PickupSound = nullptr;
};
