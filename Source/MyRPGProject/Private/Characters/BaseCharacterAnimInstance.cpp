// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacterAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/MyStatComponent.h"
#include "Interface/PlayerStateInterface.h"


UBaseCharacterAnimInstance::UBaseCharacterAnimInstance()
{

}

void UBaseCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	IPlayerStateInterface* PlayerState = Cast<IPlayerStateInterface>(TryGetPawnOwner());
	if (PlayerState)
	{
		Stat = PlayerState->GetMyStatComponent();
	}
}

void UBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 플레이어 기본 제공 상태
	ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character)
	{
		Speed = Character->GetVelocity().Size();
		Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
		IsFalling = Character->GetMovementComponent()->IsFalling();
	}

	// 플레이어 추가 상태
	IPlayerStateInterface* PlayerState = Cast<IPlayerStateInterface>(TryGetPawnOwner());
	if (PlayerState)
	{
		IsDoubleJumping = PlayerState->GetIsDoubleJumping();
		IsCrouched = PlayerState->GetIsCrouch();
		WeaponIdx = PlayerState->GetCurrentWeaponIndex();
		IsOnWall = PlayerState->GetIsOnWall();
		IsClimbingUp = PlayerState->GetIsClibmingUp();
		IsDeath = PlayerState->GetIsDeath();
	}
}

void UBaseCharacterAnimInstance::PlayDefaultAttackMontage()
{
	Montage_Play(AttackMontage_Default, 1.f);
}

void UBaseCharacterAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage_SwordDefault, 1.f);
}

void UBaseCharacterAnimInstance::PlayAttackMontageQ()
{
	Montage_Play(AttackMontage_Q, 1.f);
}

void UBaseCharacterAnimInstance::PlayAttackMontageE()
{
	Montage_Play(AttackMontage_E, 1.f);
}

void UBaseCharacterAnimInstance::PlayAttackMontageR()
{
	Montage_Play(AttackMontage_R, 1.f);
}

void UBaseCharacterAnimInstance::PlayBowAttackMontage()
{
	Montage_Play(BowAttackMontage, 1.f);
}

void UBaseCharacterAnimInstance::PlayClimbingUp()
{
	Montage_Play(ClimbingMontage, 1.f);
}

void UBaseCharacterAnimInstance::PlayClimbingComplete()
{
	Montage_Play(ClimbingCompleteMontage, 1.f);
}

void UBaseCharacterAnimInstance::JumpToSection_Default(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontage_Default);
}

void UBaseCharacterAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontage_SwordDefault);
}

FName UBaseCharacterAnimInstance::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UBaseCharacterAnimInstance::AnimNotify_AttackHit()
{
	if (Stat)
	{
		TraceDistance = Stat->GetTotalStat().AttackRange;
		OnAttackHit.Broadcast(Stat->GetTotalStat().Attack, TraceDistance, AttackParticle);
	}
}

void UBaseCharacterAnimInstance::AnimNotify_AttackHit_Q()
{
	if (Stat)
	{
		TraceDistance = Stat->GetTotalStat().AttackRange * 300.f;
		OnAttackHit_Q.Broadcast(Stat->GetTotalStat().AttackQ, TraceDistance, AttackParticleQ);
	}
}

void UBaseCharacterAnimInstance::AnimNotify_AttackHit_E()
{
	if (Stat)
	{
		TraceDistance = Stat->GetTotalStat().AttackRange * 500.f;
		OnAttackHit_E.Broadcast(Stat->GetTotalStat().AttackE, TraceDistance, AttackParticleE);
	}
}

void UBaseCharacterAnimInstance::AnimNotify_AttackHit_R()
{
	if (Stat)
	{
		TraceDistance = Stat->GetTotalStat().AttackRange * 700.f;
		OnAttackHit_R.Broadcast(Stat->GetTotalStat().AttackR, TraceDistance, nullptr);
	}
}

void UBaseCharacterAnimInstance::AnimNotify_CamShakeHit()
{
	OnCameraShake.Broadcast();
	// UE_LOLGEFfel
}



