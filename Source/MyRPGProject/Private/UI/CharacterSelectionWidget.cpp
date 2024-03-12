// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterSelectionWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/CharacterSelection.h"
#include "GameData/CharacterEnum.h"
#include "Interface/MyGameInstanceInterface.h"


void UCharacterSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SelectorActor = Cast<ACharacterSelection>(UGameplayStatics::GetActorOfClass(this, CurrentCharSelect));

}

void UCharacterSelectionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_Greystone->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::PressGreystoneBtn);
	Btn_Countess->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::PressCountessBtn);

	Btn_SelectCharacter->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::PressSelectBtn);

	NextBtn->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::PressNextBtn);
	BeforeBtn->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::PressBeforeBtn);

}

void UCharacterSelectionWidget::PressGreystoneBtn()
{
	SelectorActor->SelectCharacter(ECharacterType::CHAR_GreyStone);
	NowCharacterType = ECharacterType::CHAR_GreyStone;
}

void UCharacterSelectionWidget::PressCountessBtn()
{
	SelectorActor->SelectCharacter(ECharacterType::CHAR_Countess);
	NowCharacterType = ECharacterType::CHAR_Countess;
}

void UCharacterSelectionWidget::PressSelectBtn()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
	IMyGameInstanceInterface* GameInstance = Cast<IMyGameInstanceInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->SetCharacterType(NowCharacterType);
		GameInstance->SetCharacterMeshIndex(SelectorActor->CharacterMeshIdx);
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName("BattleMap"), true);
}

void UCharacterSelectionWidget::PressNextBtn()
{
	SelectorActor->NextOrBefore(NowCharacterType, true);
}

void UCharacterSelectionWidget::PressBeforeBtn()
{
	SelectorActor->NextOrBefore(NowCharacterType, false);
}

