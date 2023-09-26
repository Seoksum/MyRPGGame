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

	Btn_Greystone->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::GreystonePressed);
	Btn_Countess->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::CountessPressed);

	Btn_SelectCharacter->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::SelectPressed);

	NextBtn->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::NextButtonPressed);
	BeforeBtn->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::BeforeButtonPressed);

}

void UCharacterSelectionWidget::GreystonePressed()
{
	SelectorActor->SelectCharacter(ECharacterIndex::Greystone);
	NowCharacterIndex = ECharacterIndex::Greystone;
}

void UCharacterSelectionWidget::CountessPressed()
{
	SelectorActor->SelectCharacter(ECharacterIndex::Countess);
	NowCharacterIndex = ECharacterIndex::Countess;
}

void UCharacterSelectionWidget::SelectPressed()
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
		GameInstance->SetCharacterTypeIndex(NowCharacterIndex);
		GameInstance->SetCharacterMeshIndex(SelectorActor->CharacterMeshIdx);
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("ZeroMap"), true);
}

void UCharacterSelectionWidget::NextButtonPressed()
{
	SelectorActor->NextOrBefore(NowCharacterIndex, true);
}

void UCharacterSelectionWidget::BeforeButtonPressed()
{
	SelectorActor->NextOrBefore(NowCharacterIndex, false);
}

