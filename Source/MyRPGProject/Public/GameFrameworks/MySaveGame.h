// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UMySaveGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	FString SaveSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 RetryCount;

	
};
