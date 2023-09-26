// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterSelectController.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API ACharacterSelectController : public APlayerController
{
	GENERATED_BODY()

public:
	ACharacterSelectController();

	virtual void BeginPlay() override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> SelectWidgetClass;

	UUserWidget* SelectWidget;
	
};
