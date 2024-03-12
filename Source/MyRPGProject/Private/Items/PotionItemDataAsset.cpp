// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PotionItemDataAsset.h"
#include "Characters/Character_Parent.h"
#include "Components/MyStatComponent.h"

void UPotionItemDataAsset::Use(ACharacter_Parent* PlayerCharacter)
{
	Super::Use(PlayerCharacter);

	if (PlayerCharacter)
	{
		UMyStatComponent* Stat = PlayerCharacter->GetMyStatComponent();
		if (Stat)
		{
			if (PotionType == EPotionType::POTION_HP)
			{
				Stat->UseHpPotion(HpPotionAmount);
			}
			else if (PotionType == EPotionType::POTION_MANA)
			{
				Stat->UseManaPotion(ManaPotionAmount);
			}
		}
	}
}