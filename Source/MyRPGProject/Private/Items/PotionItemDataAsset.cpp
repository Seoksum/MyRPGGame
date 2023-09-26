// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PotionItemDataAsset.h"
#include "Characters/Character_Parent.h"
#include "Components/MyStatComponent.h"

void UPotionItemDataAsset::Use(ACharacter_Parent* PlayerCharacter)
{
	Super::Use(PlayerCharacter);

	if (!PlayerCharacter)
		return;

	UMyStatComponent* Stat = PlayerCharacter->GetMyStatComponent();
	if (Stat)
	{
		if (ItemName.EqualTo(FText::FromString("HpPotion")))
		{
			Stat->UseHpPotion(IncreasingVal); // HpPotionVal = 15.f;
		}
		else if (ItemName.EqualTo(FText::FromString("ManaPotion")))
		{
			Stat->UseManaPotion(IncreasingVal); // ManaPotionVal = 15.f;
		}
	}
	
}