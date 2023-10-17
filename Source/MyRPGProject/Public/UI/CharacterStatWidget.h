// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/CharacterStat.h"
#include "CharacterStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API UCharacterStatWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	TWeakObjectPtr<class UMyStatComponent> CurrentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_CurrentHp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_MaxHp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_CurrentMana;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_MaxMana;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_BaseAttack;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_WeaponAttack;
	
};
