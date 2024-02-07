// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "MazeBFL.h"
#include "MazeHUD.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
 	SetIsReplicated(true);
	
	// ...
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(UInventoryComponent, InventoryItems, COND_OwnerOnly);
}

void UInventoryComponent::AddItem_Implementation(const FItemData NewItem)
{
	InventoryItems.Add(NewItem);
}

void UInventoryComponent::OnRep_InventoryItems()
{
	AMazeHUD* MazeHUD = UMazeBFL::GetMazeHUD(this);
	if (MazeHUD)
	{
		MazeHUD->UpdateInventoryList();
	}
	if (PickupSound)
	{
		UGameplayStatics::PlaySound2D(this, PickupSound);
	}
}