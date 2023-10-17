// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/MyGameSingleton.h"
#include "Algo/Transform.h"

DEFINE_LOG_CATEGORY(LogMyGameSingleton);

UMyGameSingleton::UMyGameSingleton()
{
	// ������ ���̺� �޾ƿ��� 
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

	MaxLevel = CharacterStatTable.Num();
	
}

UMyGameSingleton& UMyGameSingleton::Get()
{
	// TODO: ���⿡ return ���� �����մϴ�.
	UMyGameSingleton* Singleton = CastChecked<UMyGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogMyGameSingleton, Error, TEXT("Invalid Game Singleton"));
	return *NewObject<UMyGameSingleton>();
}

FCharacterStat UMyGameSingleton::GetCharacterStat(int32 Level)
{
	if (Level >= 0 && Level <= MaxLevel)
	{
		return CharacterStatTable[Level];
	}
	return FCharacterStat();
}

//return CharacterStatTable.IsValidIndex(InLevel) ? CharacterStatTable[InLevel] : FCharacterStat();

