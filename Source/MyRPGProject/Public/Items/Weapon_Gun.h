// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapon.h"
#include "Weapon_Gun.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API AWeapon_Gun : public AWeapon
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWeapon_Gun();

protected:
	virtual void BeginPlay() override;

	void Attack() override;

public:

	void StartFire();
	void StopFire();

	void PlayFireEffects(FVector TraceEndPoint);
	void PlayImpactEffects(FVector ImpactPoint, UParticleSystem* Particle);


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<class UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	class UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	class UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	class UParticleSystem* BloodImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	class UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UCameraShakeBase> FireCamShake;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float TraceDistance;

public:

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFiredTime;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float RateOfFire; 	// �� �� �߻�� �Ѿ� ����

	float TimeBetweenShots;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* FireSound;




};