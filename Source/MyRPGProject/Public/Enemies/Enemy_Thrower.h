// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/Enemy.h"
#include "Enemy_Thrower.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API AEnemy_Thrower : public AEnemy
{
	GENERATED_BODY()
	
public:
	AEnemy_Thrower();


	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:

	virtual void Attack() override;

	void ThrowProjectile();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyProjectile> ProjectileClass;

	UPROPERTY()
	class AEnemyProjectile* Projectile;

};
