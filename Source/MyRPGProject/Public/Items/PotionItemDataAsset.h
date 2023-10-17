// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemDataAsset.h"
#include "PotionItemDataAsset.generated.h"

/**
 *
 */
UCLASS()
class MYRPGPROJECT_API UPotionItemDataAsset : public UItemDataAsset
{
	GENERATED_BODY()

public:
	virtual void Use(class ACharacter_Parent* PlayerCharacter) override;

public:

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("ItemDataAsset", GetFName());
	}

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		float IncreasingVal = 15.f;


};
