// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AnimInstance_Greystone.h"
#include "Characters/Character_Greystone.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/MyStatComponent.h"



UAnimInstance_Greystone::UAnimInstance_Greystone()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_DefaultAttack(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Greystone/Montages/Attack_Default.Attack_Default'"));
	if (Montage_DefaultAttack.Succeeded())
	{
		AttackMontage_Default = Montage_DefaultAttack.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_SwordDefaultAttack(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Greystone/Montages/Attack_SwordDefault.Attack_SwordDefault'"));
	if (Montage_SwordDefaultAttack.Succeeded())
	{
		AttackMontage_SwordDefault = Montage_SwordDefaultAttack.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_AttackQ(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Greystone/Montages/Attack_SwordQ.Attack_SwordQ'"));
	if (Montage_AttackQ.Succeeded())
	{
		AttackMontage_Q = Montage_AttackQ.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_AttackE(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Greystone/Montages/Attack_SwordE.Attack_SwordE'"));
	if (Montage_AttackE.Succeeded())
	{
		AttackMontage_E = Montage_AttackE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_AttackR(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Greystone/Montages/Attack_SwordR.Attack_SwordR'"));
	if (Montage_AttackR.Succeeded())
	{
		AttackMontage_R = Montage_AttackR.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_ClimbingComplete(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Greystone/Montages/ClimbingComplete.ClimbingComplete'"));
	if (Montage_ClimbingComplete.Succeeded())
	{
		ClimbingCompleteMontage = Montage_ClimbingComplete.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_Bow(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Greystone/Montages/Bow_AttackDefault.Bow_AttackDefault'"));
	if (Montage_Bow.Succeeded())
	{
		BowAttackMontage = Montage_Bow.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_Climbing(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Greystone/Montages/Climbing.Climbing'"));
	if (Montage_Climbing.Succeeded())
	{
		ClimbingMontage = Montage_Climbing.Object;
	}
}

void UAnimInstance_Greystone::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	IPlayerStateInterface* PlayerState = Cast< IPlayerStateInterface>(TryGetPawnOwner());
	if (PlayerState)
	{
		Stat = PlayerState->GetMyStatComponent();
	}
}

void UAnimInstance_Greystone::NativeUpdateAnimation(float DeltaSeconds)
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
	IPlayerStateInterface* PlayerState = Cast< IPlayerStateInterface>(TryGetPawnOwner());
	if (PlayerState)
	{
		IsDoubleJumping = PlayerState->GetIsDoubleJumping();
		IsJumping = PlayerState->GetIsJumping();
		IsCrouched = PlayerState->GetIsCrouch();
		WeaponIdx = PlayerState->GetCurrentWeaponIndex();
		IsOnWall = PlayerState->GetIsOnWall();
		IsClimbingUp = PlayerState->GetIsClibmingUp();
		IsDeath = PlayerState->GetIsDeath();
	}
}

void UAnimInstance_Greystone::PlayDefaultAttackMontage()
{
	Montage_Play(AttackMontage_Default, 1.f);
}

void UAnimInstance_Greystone::PlayAttackMontage()
{
	Montage_Play(AttackMontage_SwordDefault, 1.f);
}

void UAnimInstance_Greystone::PlayAttackMontageQ()
{
	Montage_Play(AttackMontage_Q, 1.f);
}

void UAnimInstance_Greystone::PlayAttackMontageE()
{
	Montage_Play(AttackMontage_E, 1.f);
}

void UAnimInstance_Greystone::PlayAttackMontageR()
{
	Montage_Play(AttackMontage_R, 1.f);
}

void UAnimInstance_Greystone::PlayBowAttackMontage()
{
	Montage_Play(BowAttackMontage, 1.f);
}

void UAnimInstance_Greystone::PlayClimbingComplete()
{
	Montage_Play(ClimbingCompleteMontage, 1.f);
}

float UAnimInstance_Greystone::PlayClimbing()
{
	return Montage_Play(ClimbingMontage, 1.f);
}

void UAnimInstance_Greystone::JumpToSection_Default(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontage_Default);
}

void UAnimInstance_Greystone::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontage_SwordDefault);
}

FName UAnimInstance_Greystone::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UAnimInstance_Greystone::AnimNotify_AttackHit_Q()
{
	if (Stat)
	{
		TraceDistance = Stat->GetTotalStat().AttackRange * 300.f;
		OnAttackHit_Q.Broadcast(Stat->GetTotalStat().AttackQ, TraceDistance, AttackQ_Effect);
	}
}

void UAnimInstance_Greystone::AnimNotify_AttackHit_E()
{
	if (Stat)
	{
		TraceDistance = Stat->GetTotalStat().AttackRange * 500.f;
		OnAttackHit_E.Broadcast(Stat->GetTotalStat().AttackE, TraceDistance, AttackE_Effect);
	}
}

void UAnimInstance_Greystone::AnimNotify_AttackHit_R()
{
	if (Stat)
	{
		TraceDistance = Stat->GetTotalStat().AttackRange * 700.f;
		OnAttackHit_R.Broadcast(Stat->GetTotalStat().AttackR, TraceDistance, nullptr);
	}
}

void UAnimInstance_Greystone::AnimNotify_CamShakeHit()
{
	OnCameraShake.Broadcast();
}


