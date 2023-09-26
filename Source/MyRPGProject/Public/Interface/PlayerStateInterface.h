// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerStateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYRPGPROJECT_API IPlayerStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool GetIsDoubleJumping() = 0;
	virtual int32 GetCurrentWeaponIndex() = 0;
	virtual bool GetIsOnWall() = 0;
	virtual bool GetIsClibmingUp() = 0;
	virtual bool GetIsDeath() = 0;

	virtual class UMyStatComponent* GetMyStatComponent() = 0;
	virtual class UInventoryComponent* GetInventoryComponent() = 0;
};
