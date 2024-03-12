// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponItemDataAsset.h"
#include "Characters/Character_Parent.h"
#include "GameData/CharacterEnum.h"



void UWeaponItemDataAsset::Use(ACharacter_Parent* PlayerCharacter)
{
	Super::Use(PlayerCharacter);

	if (PlayerCharacter)
	{
		if (WeaponMesh.IsPending())
		{
			WeaponMesh.LoadSynchronous();
		}
		PlayerCharacter->SwitchWeapon(WeaponType, this);
	}
}
