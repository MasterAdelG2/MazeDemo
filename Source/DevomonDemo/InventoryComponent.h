// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DevomonDemo.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVOMONDEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Adds an Item to the Inventory
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddItem(const FItemData NewItem);
	// On Iventory Items Changed
	UFUNCTION()
	void OnRep_InventoryItems();
		
	// All Inventory Items Player has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_InventoryItems, Category = "ItemData")
	TArray< FItemData> InventoryItems;
	// All Inventory Items Player has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	class USoundBase* PickupSound;
};
