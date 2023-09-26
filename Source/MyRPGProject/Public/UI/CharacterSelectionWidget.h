// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API UCharacterSelectionWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized();

	// 버튼 이벤트
protected:
	UFUNCTION()
	void GreystonePressed();

	UFUNCTION()
	void CountessPressed();

	UFUNCTION()
	void SelectPressed();

	UFUNCTION()
	void NextButtonPressed();

	UFUNCTION()
	void BeforeButtonPressed();

	// 버튼
private:

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Greystone;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Countess;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_SelectCharacter;

	UPROPERTY(meta = (BindWidget))
	class UButton* NextBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* BeforeBtn;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterSelection")
	TSubclassOf<class ACharacterSelection> CurrentCharSelect;

	UPROPERTY(EditDefaultsOnly)
	class ACharacterSelection* SelectorActor;

	UPROPERTY()
	int32 NowCharacterIndex = 0;


};
