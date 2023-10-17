// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/CharacterStat.h"
#include "InGame.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API UInGame : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	virtual void NativeConstruct() override;

public:

	UInGame(const FObjectInitializer& ObjectInitializer);

	void SetGreystone(int32 PlayerLevel);
	void SetCountess(int32 PlayerLevel);

	void SetCharacterImage(FString QPath, FString EPath, FString RPath, FString Thumbnail);

	void BindStat(class UMyStatComponent* StatComp);

	void SetLevel(int32 PlayerLevel);
	

	void UpdateHp(float Hp);

	void UpdateMana(float Mana, float MaxMana);

	void UpdateAttack(float WeaponAttack);

	void UpdatePlayerStat(const FCharacterStat& CharacterStat);

	void UpdateRetryCount(int32 NewRetryCount);


public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Level;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_RetryCount;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Q;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_E;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_R;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Q;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_E;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_R;

	UPROPERTY(meta = (BindWidget))
	class UCharacterStatWidget* CharacterStatWidget;

	UPROPERTY(meta = (BindWidget))
	class UHPWidget* StatBarWidget;


private:

	TWeakObjectPtr<class UMyStatComponent> CurrentStatComp;


};
