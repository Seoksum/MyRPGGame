// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/MyStatComponent.h"


void UHPWidget::BindHp(class UMyStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	CurrentStatComp->OnHpChanged.AddUObject(this, &UHPWidget::UpdateHp);
}

void UHPWidget::UpdateHp(float Hp)
{
	if (CurrentStatComp.IsValid())
	{
		PB_HpBar->SetPercent(Hp / CurrentStatComp->GetMaxHp());
	}
}

void UHPWidget::BindMana(class UMyStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	CurrentStatComp->OnManaChanged.AddUObject(this, &UHPWidget::UpdateMana);
}

void UHPWidget::UpdateMana(float Mana, float MaxMana)
{
	if (CurrentStatComp.IsValid())
		PB_ManaBar->SetPercent(Mana / MaxMana);
}
