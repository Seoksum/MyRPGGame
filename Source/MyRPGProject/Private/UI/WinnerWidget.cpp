// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WinnerWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFrameworks/MyGameInstance.h"


void UWinnerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RestartButton->OnClicked.AddDynamic(this, &UWinnerWidget::RestartGame);
}

void UWinnerWidget::RestartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("CharSelectMap"));
}
