// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameData/CharacterEnum.h"
#include "MyGameInstanceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMyGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYRPGPROJECT_API IMyGameInstanceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void SetCharacterType(ECharacterType InCharacterType) = 0;
	virtual void SetCharacterMeshIndex(int32 InCharacterMesh) = 0;

	virtual TMap<int32, FName> GetWeaponMap() = 0;
	

};
