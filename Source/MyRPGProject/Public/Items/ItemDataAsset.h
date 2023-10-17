// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon = 0,
	Potion,
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
	EItemType Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY()
	TWeakObjectPtr<class UInventoryComponent> OwingInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText UseActionText;

};
