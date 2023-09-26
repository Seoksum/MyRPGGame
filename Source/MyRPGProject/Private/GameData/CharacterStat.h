
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCharacterStat() : Attack(0.f), AttackQ(0.f), AttackE(0.f), AttackR(0.f),
		MaxHp(0.f), MaxMana(0.f), Exp(0.f), Mana(0.f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float AttackQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float AttackE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float AttackR;

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
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&other);
		
		FCharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 statNum = sizeof(FCharacterStat) / sizeof(float);
		for (int32 i = 0; i < statNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}
		return Result;
	}



};

