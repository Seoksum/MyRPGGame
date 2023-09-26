// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/WeaponItemDataAsset.h"
#include "WeaponItemDataAsset_Bow.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API UWeaponItemDataAsset_Bow : public UWeaponItemDataAsset
{
	GENERATED_BODY()

public:

	UWeaponItemDataAsset_Bow();

	virtual void WeaponAttack(class ACharacter_Parent* InPlayer) override;
	void Fire();


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<class AArrow> ArrowClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class AArrow* Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float ArrowSpeedVal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	class USoundBase* ShootSound;

	
};
