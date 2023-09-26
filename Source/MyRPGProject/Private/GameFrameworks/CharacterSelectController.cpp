// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameworks/CharacterSelectController.h"
#include "UI/CharacterSelectionWidget.h"
#include "Kismet/GameplayStatics.h"


ACharacterSelectController::ACharacterSelectController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> SelectWidget_Class(TEXT("WidgetBlueprint'/Game/UI/WBP_CharacterSelection.WBP_CharacterSelection_C'"));
	if (SelectWidget_Class.Succeeded())
	{
		SelectWidgetClass = SelectWidget_Class.Class;
	}
}

void ACharacterSelectController::BeginPlay()
{
	Super::BeginPlay();
	
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	SelectWidget = CreateWidget(GetWorld(), SelectWidgetClass);
	SelectWidget->AddToViewport();
}


