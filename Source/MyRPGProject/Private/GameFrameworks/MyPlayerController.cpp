// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameworks/MyPlayerController.h"
#include "UI/InGame.h"
//#include "UI/WinnerWidget.h"
//#include "UI/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "GameFrameworks/MySaveGame.h"



AMyPlayerController::AMyPlayerController()
{
	static ConstructorHelpers::FClassFinder<UInGame> Ingame_Class(TEXT("WidgetBlueprint'/Game/UI/WBP_InGame.WBP_InGame_C'"));
	if (Ingame_Class.Succeeded())
	{
		IngameHUDClass = Ingame_Class.Class;
		InGameWidget = CreateWidget<UInGame>(GetWorld(), IngameHUDClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> Inventory_Class(TEXT("WidgetBlueprint'/Game/UI/WBP_Inventory.WBP_Inventory_C'"));
	if (Inventory_Class.Succeeded())
	{
		InventoryHUDClass = Inventory_Class.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> Restart_Class(TEXT("WidgetBlueprint'/Game/UI/WBP_Restart.WBP_Restart_C'"));
	if (Restart_Class.Succeeded())
	{
		RestartHUDClass = Restart_Class.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> Winner_Class(TEXT("WidgetBlueprint'/Game/UI/WBP_Win.WBP_Win_C'"));
	if (Winner_Class.Succeeded())
	{
		WinnerHUDClass = Winner_Class.Class;
	}

	HUDState = EHUDState::HS_Ingame;
	
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InventoryWidget = CreateWidget(GetWorld(), InventoryHUDClass);
	RestartWidget = CreateWidget(GetWorld(), RestartHUDClass);
	WinnerWidget = CreateWidget(GetWorld(), WinnerHUDClass);
	if (InGameWidget)
	{
		InGameWidget->AddToViewport();
	}

	MySaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MyRPGGame"), 0));
	if (MySaveGame)
	{
		MySaveGame->RetryCount++;
	}
	else
	{
		MySaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		MySaveGame->RetryCount = 0;
	}
	
	InGameWidget->UpdateRetryCount(MySaveGame->RetryCount);

	UGameplayStatics::SaveGameToSlot(MySaveGame, MySaveGame->SaveSlotName, 0);
}

void AMyPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();



}

void AMyPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner)
	{
		//ApplyHUD(WinnerWidget, true, true);
		ChangeHUD(HS_Win);
	}
	else
	{
		// LoseScreen 화면 출력
		ChangeHUD(HS_Restart);
	}

}

void AMyPlayerController::RestartLevel()
{
	Super::RestartLevel();

}

void AMyPlayerController::ApplyHUDChanges()
{

	switch (HUDState)
	{
	case EHUDState::HS_Inventory:
		ApplyHUD(InventoryWidget, true, true);
		break;

	case EHUDState::HS_Restart:
		ApplyHUD(RestartWidget, true, true);
		break;
	case EHUDState::HS_Win:
		ApplyHUD(WinnerWidget, true, true);
		break;

	default:
		//ApplyHUD(InGameWidget, false, false);
		break;
	}
}

uint8 AMyPlayerController::GetHUDState()
{
	return HUDState;
}

void AMyPlayerController::ChangeHUD(uint8 NewState)
{
	HUDState = NewState;
	ApplyHUDChanges();
}

void AMyPlayerController::RemoveHUD(uint8 NewState)
{
	switch (NewState)
	{
	case EHUDState::HS_Inventory:
		InventoryWidget->RemoveFromViewport();
		break;
	
	case EHUDState::HS_Restart:
		RestartWidget->RemoveFromViewport();
		break;
	
	default:
		break;
	
	}
	bShowMouseCursor = false;
	bEnableClickEvents = false;
}

bool AMyPlayerController::ApplyHUD(UUserWidget* WidgetToApply, bool IsShowMouseCursor, bool IsEnableClickEvents)
{
	// 적용하기전 위젯 체크
	if (WidgetToApply)
	{
		bShowMouseCursor = IsShowMouseCursor;
		bEnableClickEvents = IsEnableClickEvents;

		WidgetToApply->AddToViewport();
		return true;
	}
	return false;
}

