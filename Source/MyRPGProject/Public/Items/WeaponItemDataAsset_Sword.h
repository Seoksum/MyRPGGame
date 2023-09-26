// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/WeaponItemDataAsset.h"
#include "WeaponItemDataAsset_Sword.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API UWeaponItemDataAsset_Sword : public UWeaponItemDataAsset
{
	GENERATED_BODY()
	
public:

	virtual void WeaponAttack(class ACharacter_Parent* InPlayer) override;


};
