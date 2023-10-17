// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameworks/MyGameInstance.h"


UMyGameInstance::UMyGameInstance()
{
	CharacterTypeIdx = 0;
	CharacterMeshIdx = 0;

	WeaponCount = 4;
}

void UMyGameInstance::Init()
{
	Super::Init();
	
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EWeapon"), true);
	if (enumPtr != nullptr)
	{
		for (int32 i = 1; i < WeaponCount; i++) // 0¹øÀº None
		{
			const FName WeaponName = *FString::Printf(TEXT("%sSocket"), *enumPtr->GetNameByIndex(i).ToString());
			WeaponArray.Add(i, WeaponName);
		}
	}

}

void UMyGameInstance::SetCharacterTypeIndex(int32 CharacterType)
{
	CharacterTypeIdx = CharacterType;
}

void UMyGameInstance::SetCharacterMeshIndex(int32 CharacterMesh)
{
	CharacterMeshIdx = CharacterMesh;
}

TMap<int32, FName> UMyGameInstance::GetWeaponArray()
{
	return WeaponArray;
}



