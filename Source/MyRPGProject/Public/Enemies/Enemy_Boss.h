// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/Enemy.h"
#include "Interface/EnemyAIInterface.h"
#include "Interface/AIEnemyInterface.h"
#include "Enemy_Boss.generated.h"

/**
 * 
 */



UCLASS()
class MYRPGPROJECT_API AEnemy_Boss : public AEnemy, public IAIEnemyInterface
{
	GENERATED_BODY()


public:

	AEnemy_Boss();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	virtual bool IsBossEnemyDead() override;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	virtual void Attack() override;
	
	void AttackCheck();

	void SkillAttack();

	virtual void Landed(const FHitResult& Hit) override;


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
	class UParticleSystem* SkillEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		class UParticleSystem* JumpEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool JumpAttacking;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TSubclassOf<UCameraShakeBase> AttackedCamShake;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	class USkeletalMeshComponent* WeaponLeft;

	UPROPERTY()
	int32 AttackIndex = 0;

	

};
