// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameworks/MyGameInstance.h"
#include "GameData/CharacterEnum.h"


UMyGameInstance::UMyGameInstance()
{
	CharacterType = ECharacterType::CHAR_GreyStone;
	CharacterMeshIdx = 0;

	WeaponCount = 3;
}

void UMyGameInstance::Init()
{
	Super::Init();
	
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EWeaponType"), true);
	if (enumPtr != nullptr)
	{
		for (int32 i = 1; i <= WeaponCount; i++)
		{
			const FName WeaponName = *FString::Printf(TEXT("%s_SOCKET"), *enumPtr->GetNameByIndex(i).ToString());
			WeaponMap.Add(i, WeaponName);
		}
	}
}

void UMyGameInstance::SetCharacterType(ECharacterType InCharacterType)
{
	CharacterType = InCharacterType;
}

void UMyGameInstance::SetCharacterMeshIndex(int32 InCharacterMesh)
{
	CharacterMeshIdx = InCharacterMesh;
}

TMap<int32, FName> UMyGameInstance::GetWeaponMap()
{
	return WeaponMap;
}



