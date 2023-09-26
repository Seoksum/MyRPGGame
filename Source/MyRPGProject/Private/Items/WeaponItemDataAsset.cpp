// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponItemDataAsset.h"
#include "Characters/Character_Parent.h"
#include "GameData/CharacterEnum.h"



void UWeaponItemDataAsset::Use(ACharacter_Parent* PlayerCharacter)
{
	Super::Use(PlayerCharacter);

	if (!PlayerCharacter)
		return;

	if (ItemName.EqualTo(FText::FromString("WeaponSword")))
	{
		PlayerCharacter->SwitchWeaponItemData(EWeapon::Sword, this);
	}
	else if (ItemName.EqualTo(FText::FromString("WeaponGun")))
	{
		PlayerCharacter->SwitchWeaponItemData(EWeapon::Gun,this);
	}
	else if (ItemName.EqualTo(FText::FromString("WeaponBow")))
	{
		PlayerCharacter->SwitchWeaponItemData(EWeapon::Bow,this);
	}
}

void UWeaponItemDataAsset::WeaponAttack(ACharacter_Parent* InPlayer)
{
	

}
