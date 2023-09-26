// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ChangeHUDInterface.generated.h"


UENUM()
enum EHUDStates
{
	HS_Ingame,
	HS_Inventory,
	HS_Restart,
	HS_Win,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UChangeHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYRPGPROJECT_API IChangeHUDInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	uint8 HUDState;

	virtual void ChangeHUD(uint8 NewState) = 0;
	virtual void RemoveHUD(uint8 NewState) = 0;
};
