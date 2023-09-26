// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYRPGPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UInventoryComponent();

	virtual void BeginPlay() override;

	void AddItemData(class UItemDataAsset* Item);

	void RemoveItemData(class UItemDataAsset* Item);

	FORCEINLINE TArray<class UItemDataAsset*> GetDefaultItems() {return DefaultItems;}
	FORCEINLINE TArray<class UItemDataAsset*> GetItemDataArray() {return ItemDataArray;}

private:

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity;

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UItemDataAsset*> DefaultItems;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<class UItemDataAsset*> ItemDataArray;

public:
	FOnInventoryUpdated OnInventoryUpdated;

};
