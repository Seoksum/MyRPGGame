// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemyHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/MyStatComponent.h"


void UEnemyHPWidget::BindHp(class UMyStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	CurrentStatComp->OnHpChanged.AddUObject(this, &UEnemyHPWidget::UpdateHp);
	
}

void UEnemyHPWidget::UpdateHp(float Hp)
{
	if (CurrentStatComp.IsValid())
		PB_HpBar->SetPercent(Hp / CurrentStatComp->GetMaxHp());
}

void UEnemyHPWidget::BindLevel(int32 Level)
{
	const FString MyLevel = FString::Printf(TEXT("%d"), Level);
	LevelText->SetText(FText::FromString(MyLevel));

}
