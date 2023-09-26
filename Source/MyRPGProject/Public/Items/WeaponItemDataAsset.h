// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemDataAsset.h"
#include "GameData/CharacterStat.h"
#include "WeaponItemDataAsset.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	Sword,
	Gun,
	Bow,
};

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API UWeaponItemDataAsset : public UItemDataAsset
{
	GENERATED_BODY()
	
public:

	virtual void Use(class ACharacter_Parent* PlayerCharacter) override;

	virtual void WeaponAttack(class ACharacter_Parent* InPlayer);

public:

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("ItemDataAsset", GetFName());
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, Category = "WeaponMesh")
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "WeaponMesh")
	TSoftObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Stat")
	FCharacterStat WeaponStat;


protected:

	UPROPERTY(VisibleAnywhere,Category="Player")
	class ACharacter_Parent* Player;

	
};
