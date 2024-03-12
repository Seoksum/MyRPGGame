// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "GameData/CharacterEnum.h"
#include "GameData/CharacterStat.h"
#include "Weapon.generated.h"

UCLASS()
class MYRPGPROJECT_API AWeapon : public AItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	virtual void Use(class ACharacter_Parent* PlayerCharacter);

	virtual void PostInitializeComponents() override;

protected:
	
	virtual void BeginPlay() override;

public:

	EWeaponType WeaponType;

	virtual void Attack();
	virtual void Attack(int32 damage, float TraceDistance, class UParticleSystem* Particle);


};
