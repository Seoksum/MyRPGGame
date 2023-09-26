// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_Countess.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAttackHit, int32, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAttackHit_Q, int32, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAttackHit_E, int32, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAttackHit_R, int32, float);

UCLASS()
class MYRPGPROJECT_API UAnimInstance_Countess : public UAnimInstance
{
	GENERATED_BODY()


public:

	UAnimInstance_Countess();

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


	// Player State
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	bool IsDoubleJump;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* BowAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing", Meta = (AllowPrivateAccess = true))
	UAnimMontage* ClimbingCompleteMontage;


private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float TraceDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UMyStatComponent* Stat;


	// Delegate
public:
	FOnAttackHit OnAttackHit;
	FOnAttackHit_Q OnAttackHit_Q;
	FOnAttackHit_E OnAttackHit_E;
	FOnAttackHit_R OnAttackHit_R;

};
