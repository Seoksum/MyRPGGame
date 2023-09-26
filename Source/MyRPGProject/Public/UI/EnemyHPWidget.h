// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API UEnemyHPWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void BindHp(class UMyStatComponent* StatComp);
	void UpdateHp(float Hp);

	void BindLevel(int32 Level);


public:
	TWeakObjectPtr<class UMyStatComponent> CurrentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LevelText;


};
