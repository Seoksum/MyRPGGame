// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/WeaponItemDataAsset.h"
#include "WeaponItemDataAsset_Gun.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API UWeaponItemDataAsset_Gun : public UWeaponItemDataAsset
{
	GENERATED_BODY()
	

public:
	UWeaponItemDataAsset_Gun();

	void Fire();


public:

	virtual void WeaponAttack(class ACharacter_Parent* InPlayer) override;

	void StartFire();
	void StopFire();

	void PlayFireEffects(FVector TraceEndPoint);

	void PlayImpactEffects(FVector ImpactPoint, UParticleSystem* Particle);


public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class UParticleSystem* BloodImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UCameraShakeBase> FireCamShake;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BaseDamage;

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFiredTime = 0.f;

	// 분 당 발사된 총알 개수
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float RateOfFire;

	float TimeBetweenShots;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* FireSound;
};
