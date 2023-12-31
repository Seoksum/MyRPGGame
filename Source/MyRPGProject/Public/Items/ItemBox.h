// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBox.generated.h"

UCLASS()
class MYRPGPROJECT_API AItemBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemBox();

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;


	UPROPERTY(VisibleAnywhere, Category = "Component")
		class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		class UStaticMeshComponent* MeshComp;



public:

	UPROPERTY(EditAnywhere, Category = "Item")
	class UItemDataAsset* Item;

	UPROPERTY(EditAnywhere, Category = "Item")
	int32 WeaponCount;

	UPROPERTY(EditAnywhere, Category = "Item")
	int32 BoxIndex;


};
