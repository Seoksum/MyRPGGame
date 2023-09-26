// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame.h"
#include "UI/HPWidget.h"
#include "UI/CharacterStatWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Components/MyStatComponent.h"
#include "Interface/InGameWidgetInterface.h"
#include "Interface/ChangeHUDInterface.h"


UInGame::UInGame(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UInGame::NativeConstruct()
{
	Super::NativeConstruct();

	IInGameWidgetInterface* PlayerPawn = Cast<IInGameWidgetInterface>(GetOwningPlayerPawn());
	if (PlayerPawn)
	{
		PlayerPawn->AddInGameWidget(this);
	}

}

void UInGame::SetGreystone(int32 PlayerLevel)
{
	SetLevel(PlayerLevel);

	const FString Q_Path = "Texture2D'/Game/Images/Greystone_Q.Greystone_Q'";
	const FString E_Path = "Texture2D'/Game/Images/Greystone_E.Greystone_E'";
	const FString R_Path = "Texture2D'/Game/Images/Greystone_R.Greystone_R'";
	const FString CharacterThumbnail = "Texture2D'/Game/Images/Greystone_Image.Greystone_Image'";

	SetCharacterImage(Q_Path, E_Path, R_Path, CharacterThumbnail);
	
}

void UInGame::SetCountess(int32 PlayerLevel)
{
	SetLevel(PlayerLevel);

	const FString Q_Path = "Texture2D'/Game/Images/Countess_Q.Countess_Q'";
	const FString E_Path = "Texture2D'/Game/Images/Countess_E.Countess_E'";
	const FString R_Path = "Texture2D'/Game/Images/Countess_R.Countess_R'";
	const FString CharacterThumbnail = "Texture2D'/Game/Images/Countess_Image.Countess_Image'";

	SetCharacterImage(Q_Path, E_Path, R_Path, CharacterThumbnail);
}

void UInGame::SetCharacterImage(FString QPath, FString EPath, FString RPath, FString Thumbnail)
{
	UTexture2D* MyTexture_Q = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *QPath));
	UTexture2D* MyTexture_E = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *EPath));
	UTexture2D* MyTexture_R = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *RPath));
	UTexture2D* MyImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *Thumbnail));

	Image_Q->SetBrushFromTexture(MyTexture_Q);
	Image_E->SetBrushFromTexture(MyTexture_E);
	Image_R->SetBrushFromTexture(MyTexture_R);
}

void UInGame::BindStat(UMyStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	CurrentStatComp->OnPlayerLevelUp.AddUObject(this, &UInGame::SetLevel);
	CurrentStatComp->OnHpChanged.AddUObject(this, &UInGame::UpdateHp);
	CurrentStatComp->OnManaChanged.AddUObject(this, &UInGame::UpdateMana);
}

void UInGame::SetLevel(int32 PlayerLevel)
{
	const FString MyLevel = FString::Printf(TEXT("%d"), PlayerLevel);
	Text_Level->SetText(FText::FromString(MyLevel));
}


void UInGame::UpdateHp(float Hp)
{
	if (CurrentStatComp.IsValid())
	{
		StatBarWidget->PB_HpBar->SetPercent(Hp / CurrentStatComp->GetMaxHp());

		const FString CurrentHp = FString::Printf(TEXT("%d"), (int)Hp);
		CharacterStatWidget->Text_CurrentHp->SetText(FText::FromString(CurrentHp));
	}
}

void UInGame::UpdateMana(float Mana, float MaxMana)
{
	if (CurrentStatComp.IsValid())
	{
		StatBarWidget->PB_ManaBar->SetPercent(Mana / MaxMana);

		const FString CurrentMana = FString::Printf(TEXT("%d"), (int)Mana);
		CharacterStatWidget->Text_CurrentMana->SetText(FText::FromString(CurrentMana));
	}
}

void UInGame::UpdateAttack(float WeaponAttack)
{
	const FString Weapon_Attack = FString::Printf(TEXT("%d"), (int)WeaponAttack);
	CharacterStatWidget->Text_WeaponAttack->SetText(FText::FromString(Weapon_Attack));
}

void UInGame::UpdatePlayerStat(const FCharacterStat& CharacterStat)
{
	const FString MaxHp = FString::Printf(TEXT("%d"), (int)CharacterStat.MaxHp);
	CharacterStatWidget->Text_MaxHp->SetText(FText::FromString(MaxHp));

	const FString MaxMana = FString::Printf(TEXT("%d"), (int)CharacterStat.MaxMana);
	CharacterStatWidget->Text_MaxMana->SetText(FText::FromString(MaxMana));

	const FString Attack = FString::Printf(TEXT("%d"), (int)CharacterStat.Attack);
	CharacterStatWidget->Text_BaseAttack->SetText(FText::FromString(Attack));

}

void UInGame::UpdateRetryCount(int32 NewRetryCount)
{
	const FString RetryCount = FString::Printf(TEXT("%d"), NewRetryCount);
	Text_RetryCount->SetText(FText::FromString(RetryCount));
}
