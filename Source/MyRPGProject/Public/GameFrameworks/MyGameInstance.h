// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Interface/MyGameInstanceInterface.h"
#include "GameData/CharacterEnum.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */


UCLASS()
class MYRPGPROJECT_API UMyGameInstance : public UGameInstance, public IMyGameInstanceInterface
{
	GENERATED_BODY()


public:

	UMyGameInstance();

	virtual void Init() override;
	
	virtual void SetCharacterType(ECharacterType InCharacterType);
	virtual void SetCharacterMeshIndex(int32 InCharacterMesh);

	virtual TMap<int32, FName> GetWeaponMap();
	
	FORCEINLINE ECharacterType GetCharacterType() { return CharacterType; }
	FORCEINLINE int32 GetCharacterMeshIndex() { return CharacterMeshIdx; }


private:

	UPROPERTY(VisibleAnywhere, Category = "Character")
	ECharacterType CharacterType;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	int32 CharacterMeshIdx;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 WeaponCount;

	// Weapon Index와 Socket 이름 저장하는 Map
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TMap<int32, FName> WeaponMap;



};
