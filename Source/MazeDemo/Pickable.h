// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeDemo.h"
#include "Pickable.generated.h"

UCLASS()
class MAZEDEMO_API APickable : public AActor
{
	GENERATED_BODY()
	
private:
	/** Sphere Collision Component To Detect Picking up Pawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pickable, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollision = nullptr;
	/** Static Mesh Component To show for Picking up Pawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pickable, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Model = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	APickable();

	// Sets The Mesh to the given Item Data shape
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pickable")
	void SetModel();

	// Item properties on the Pickable object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Pickable")
	FItemData ItemData;
	
	// Material that will be applied on the Pickable object
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickable")
	class UMaterialInstance* ColorMaterial;

	// On Player Collides with the Pickable object
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
