// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyGameModeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMyGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYRPGPROJECT_API IMyGameModeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void PawnKilled(class APawn* PawnKilled) = 0;

	//virtual bool IsGameEnded() = 0;


};
