// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RestartMapWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/ChangeHUDInterface.h"


void URestartMapWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RespawnBtn->OnClicked.AddDynamic(this, &URestartMapWidget::ClickRespawnBtn);
	TitleBtn->OnClicked.AddDynamic(this, &URestartMapWidget::ClickTitleBtn);

}

void URestartMapWidget::ClickRespawnBtn()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	IChangeHUDInterface* PlayerControllerInterface = Cast<IChangeHUDInterface>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerControllerInterface)
	{
		PlayerControllerInterface->ChangeHUD(EHUDStates::HS_Ingame);
		PlayerController->RestartLevel();
	}
}

void URestartMapWidget::ClickTitleBtn()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("CharSelectMap"));
}

