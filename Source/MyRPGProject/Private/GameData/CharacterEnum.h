
#pragma once

#include "CoreMinimal.h"
#include "CharacterEnum.generated.h"

UENUM()
enum EWeapon
{
	None,
	Sword,
	Gun,
	Bow,
};

UENUM()
enum EEnemy
{
	SkeletonEnemy,
	BossEnemy,
};

UENUM()
enum ECharacterIndex
{
	Greystone,
	Countess,
};
