// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Interface/MyGameInstanceInterface.h"
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
	
	virtual void SetCharacterTypeIndex(int32 CharacterType);
	virtual void SetCharacterMeshIndex(int32 CharacterMesh);
	virtual TMap<int32, FName> GetWeaponArray();

	FORCEINLINE int32 GetCharacterTypeIndex() {return CharacterTypeIdx;}
	FORCEINLINE int32 GetCharacterMeshIndex() { return CharacterMeshIdx; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Character")
	int32 CharacterTypeIdx;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	int32 CharacterMeshIdx;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 WeaponCount;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TMap<int32, FName> WeaponArray;




};
