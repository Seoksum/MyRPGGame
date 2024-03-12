// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "GameData/CharacterEnum.h"
#include "Item_Potion.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API AItem_Potion : public AItem
{
	GENERATED_BODY()
	
public:

	AItem_Potion();

	virtual void BeginPlay() override;

	virtual void Use(class ACharacter_Parent* PlayerCharacter) override;

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Item", GetFName());
	}

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	EPotionType PotionType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0f))
	float HpPotionVal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0f))
	float ManaPotionVal;

};
