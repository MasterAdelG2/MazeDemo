// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DevomonDemo.h"
#include "Pickable.generated.h"

UCLASS()
class DEVOMONDEMO_API APickable : public AActor
{
	GENERATED_BODY()
	
private:
	/** Sphere Collision Component To Detect Picking up Pawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollision;
	/** Static Mesh Component To show for Picking up Pawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Model;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	APickable();

	//
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetModel();

	// Item properties on the Pickable object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "ItemData")
	FItemData ItemData;

	// On Player Collides with the Pickable object
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
