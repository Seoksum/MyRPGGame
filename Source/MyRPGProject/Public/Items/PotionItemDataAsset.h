// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemDataAsset.h"
#include "GameData/CharacterEnum.h"
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

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (ClampMin = 0.0f))
	float HpPotionAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (ClampMin = 0.0f))
	float ManaPotionAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EPotionType PotionType;

};
