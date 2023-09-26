// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API UHPWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	void BindHp(class UMyStatComponent* StatComp);
	void UpdateHp(float Hp);

	void BindMana(class UMyStatComponent* StatComp);
	void UpdateMana(float Mana, float MaxMana);

	

public:

	TWeakObjectPtr<class UMyStatComponent> CurrentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_ManaBar;
	
};
