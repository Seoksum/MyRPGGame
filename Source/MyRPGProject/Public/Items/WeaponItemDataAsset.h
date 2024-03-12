// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemDataAsset.h"
#include "GameData/CharacterStat.h"
#include "GameData/CharacterEnum.h"
#include "WeaponItemDataAsset.generated.h"


/**
 *
 */
UCLASS()
class MYRPGPROJECT_API UWeaponItemDataAsset : public UItemDataAsset
{
	GENERATED_BODY()

public:

	virtual void Use(class ACharacter_Parent* PlayerCharacter) override;


public:

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("ItemDataAsset", GetFName());
	}

	UPROPERTY(EditAnywhere, Category = "Stat")
	FCharacterStat WeaponStat;

	UPROPERTY(EditAnywhere, Category = "WeaponMesh")
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
	int32 WeaponType;


};
