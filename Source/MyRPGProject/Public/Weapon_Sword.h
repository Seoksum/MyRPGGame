// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Weapon_Sword.generated.h"

UCLASS()
class MYRPGPROJECT_API AWeapon_Sword : public AWeapon
{
	GENERATED_BODY()
	
public:	
	
	AWeapon_Sword();

protected:
	
	virtual void BeginPlay() override;

public:
	void AttackSword(int32 damage, float TraceDistance, class UParticleSystem* Particle);




};
