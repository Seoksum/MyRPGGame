
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStat : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Mana;

	FCharacterStat operator+(const FCharacterStat& other) const
	{
		FCharacterStat Result;

		const float* BaseStat = reinterpret_cast<const float*>(this);
		const float* WeaponStat = reinterpret_cast<const float*>(&other);
		float* ResultStat = reinterpret_cast<float*>(&Result);

		int32 StatNum = sizeof(FCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultStat[i] = BaseStat[i] + WeaponStat[i];
		}
		return Result;
	}
};

