// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameworks/MyGameInstance.h"
#include "GameData/CharacterEnum.h"


UMyGameInstance::UMyGameInstance()
{
	// 데이터 테이블 받아오기 
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("DataTable'/Game/Data/CharacterStatTable.CharacterStatTable'"));

	if (DataTable.Object)
	{
		const UDataTable* StatDataTable = DataTable.Object;

		TArray<FCharacterStat*> CharacterStats;
		StatDataTable->GetAllRows<FCharacterStat>(TEXT("GetAllRows"), CharacterStats);
		for (int32 i = 0; i < CharacterStats.Num(); ++i)
		{
			CharacterStatTable.Add(*CharacterStats[i]);
		}
	}

	CurrentLevel = 1;
	MaxLevel = CharacterStatTable.Num();

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

void UMyGameInstance::SetCurrentLevel(float InCurrentLevel)
{
	CurrentLevel = InCurrentLevel;
}

float UMyGameInstance::GetCurrentLevel()
{
	return CurrentLevel;
}

FCharacterStat UMyGameInstance::GetCharacterStat(int32 Level)
{
	if (Level >= 1 && Level < MaxLevel)
	{
		return CharacterStatTable[Level - 1];
	}
	return FCharacterStat();
}
