// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_Greystone.generated.h"

/**
 * 
 */


DECLARE_MULTICAST_DELEGATE_ThreeParams(FGOnAttackHit, int32, float,class UParticleSystem*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FGOnAttackHit_Q, int32, float, class UParticleSystem*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FGOnAttackHit_E, int32, float, class UParticleSystem*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FGOnAttackHit_R, int32, float, class UParticleSystem*);
DECLARE_MULTICAST_DELEGATE(FOnCameraShake);


UCLASS()
class MYRPGPROJECT_API UAnimInstance_Greystone : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UAnimInstance_Greystone();

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

	void PlayClimbingComplete();
	float PlayClimbing();


	// AnimNotify
private:

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage")
	UAnimMontage* AttackMontage_Default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_SwordDefault;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_Q;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_E;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_R;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* BowAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* ClimbingCompleteMontage;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", Meta = (AllowPrivateAccess = true))
		UAnimMontage* ClimbingMontage;


	// Particle System
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSystem", Meta = (AllowPrivateAccess = true))
		class UParticleSystem* AttackQ_Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSystem", Meta = (AllowPrivateAccess = true))
		class UParticleSystem* AttackE_Effect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		class UMyStatComponent* Stat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		float TraceDistance;


// Delegate
public:

	FGOnAttackHit OnAttackHit;
	FGOnAttackHit_Q OnAttackHit_Q;
	FGOnAttackHit_E OnAttackHit_E;
	FGOnAttackHit_R OnAttackHit_R;
	FOnCameraShake OnCameraShake;


};
