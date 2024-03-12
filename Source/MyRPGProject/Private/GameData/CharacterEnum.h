
#pragma once

#include "CoreMinimal.h"
#include "CharacterEnum.generated.h"

UENUM()
enum EWeaponType
{
	WEAPON_NONE,
	WEAPON_SWORD,
	WEAPON_GUN,
	WEAPON_BOW,
};

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	CHAR_GreyStone,
	CHAR_Countess,
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	ITEM_POTION,
	ITEM_WEAPON,
};

UENUM(BlueprintType)
enum class EPotionType : uint8
{
	POTION_HP = 0,
	POTION_MANA,
};



