// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseCharacterAnimInstance.generated.h"

/**
 * 
 */


DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttackHit, float, float, class UParticleSystem*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttackHit_Q, float, float, class UParticleSystem*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttackHit_E, float, float, class UParticleSystem*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttackHit_R, float, float, class UParticleSystem*);
DECLARE_MULTICAST_DELEGATE(FOnCameraShake);

UCLASS()
class MYRPGPROJECT_API UBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UBaseCharacterAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	// Play Montage
public:

	void PlayDefaultAttackMontage();
	void PlayAttackMontage();
	void PlayAttackMontageQ();
	void PlayAttackMontageE();
	void PlayAttackMontageR();
	void PlayBowAttackMontage();


	void JumpToSection_Default(int32 SectionIndex);
	void JumpToSection(int32 SectionIndex);
	FName GetAttackMontageName(int32 SectionIndex);

	void PlayClimbingUp();
	void PlayClimbingComplete();

	// AnimNotify
private:

	UFUNCTION()
	void AnimNotify_AttackHit();

	UFUNCTION()
	void AnimNotify_AttackHit_Q();

	UFUNCTION()
	void AnimNotify_AttackHit_E();

	UFUNCTION()
	void AnimNotify_AttackHit_R();

	UFUNCTION()
	void AnimNotify_CamShakeHit();


	// Player State
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	bool IsDoubleJumping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	bool IsJumping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	bool IsCrouched;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	int32 WeaponIdx;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	bool IsOnWall;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	bool IsClimbingUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	bool IsDeath;

	// Anim Montage
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Montage")
	UAnimMontage* AttackMontage_Default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_SwordDefault;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_Q;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_E;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_R;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* BowAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* ClimbingCompleteMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* ClimbingMontage;


	// Particle System
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSystem")
	class UParticleSystem* AttackParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSystem")
	class UParticleSystem* AttackParticleQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSystem")
	class UParticleSystem* AttackParticleE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UMyStatComponent* Stat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float TraceDistance;


	// Delegate
public:

	FOnAttackHit OnAttackHit;
	FOnAttackHit_Q OnAttackHit_Q;
	FOnAttackHit_E OnAttackHit_E;
	FOnAttackHit_R OnAttackHit_R;
	FOnCameraShake OnCameraShake;
};
