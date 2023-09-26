// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/MyGameModeInterface.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API AMyGameModeBase : public AGameModeBase, public IMyGameModeInterface
{
	GENERATED_BODY()
	

public:
	AMyGameModeBase();

	//virtual void PawnKilled(APawn* PawnKilled) override;

	virtual void PawnKilled(class APawn* PawnKilled);
	void EndGame(bool bIsPlayerWinner);




private:
	UPROPERTY(VisibleAnywhere)
	class UMyGameInstance* GameInstanceRef;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	int32 CharTypeIndex;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	int32 CharMeshIndex;


};
