// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponItemDataAsset_Sword.h"
#include "Components/SkeletalMeshComponent.h"
#include "Characters/Character_Parent.h"



void UWeaponItemDataAsset_Sword::WeaponAttack(ACharacter_Parent* InPlayer)
{
	Super::WeaponAttack(Player);

	Player = InPlayer;
	
}

