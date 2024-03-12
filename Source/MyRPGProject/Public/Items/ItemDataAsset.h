// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameData/CharacterEnum.h"
#include "ItemDataAsset.generated.h"

/**
 *
 */
UCLASS()
class MYRPGPROJECT_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UStaticMesh* GetLazyLoadedMesh();
	virtual void Use(class ACharacter_Parent* PlayerCharacter);


public:

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("ItemDataAsset", GetFName());
	}

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY()
	TWeakObjectPtr<class UInventoryComponent> OwingInventory;

public:

	UPROPERTY(EditAnywhere, Category = "Type")
	EItemType Type;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, Category = "Item")  // meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FText UseActionText;

};
