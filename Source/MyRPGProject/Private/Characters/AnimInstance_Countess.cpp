// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AnimInstance_Countess.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/MyStatComponent.h"
#include "Interface/PlayerStateInterface.h"

UAnimInstance_Countess::UAnimInstance_Countess()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_DefaultAttack(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Countess/Montages/Attack_Default.Attack_Default'"));
	if (Montage_DefaultAttack.Succeeded())
	{
		AttackMontage_Default = Montage_DefaultAttack.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Countess/Montages/Attack_SwordDefault.Attack_SwordDefault'"));
	if (AM.Succeeded())
	{
		AttackMontage_SwordDefault = AM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AQ(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Countess/Montages/Attack_SwordQ.Attack_SwordQ'"));
	if (AQ.Succeeded())
	{
		AttackMontage_Q = AQ.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AE(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Countess/Montages/Attack_SwordE.Attack_SwordE'"));
	if (AE.Succeeded())
	{
		AttackMontage_E = AE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AR(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Countess/Montages/Attack_SwordR.Attack_SwordR'"));
	if (AR.Succeeded())
	{
		AttackMontage_R = AR.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> CC(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Countess/Montages/ClimbingComplete.ClimbingComplete'"));
	if (CC.Succeeded())
	{
		ClimbingCompleteMontage = CC.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> BA(TEXT("AnimMontage'/Game/Blueprints/MainCharacter/Countess/Montages/Bow_AttackDefault.Bow_AttackDefault'"));
	if (BA.Succeeded())
	{
		BowAttackMontage = BA.Object;
	}
}

void UAnimInstance_Countess::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	IPlayerStateInterface* PlayerState = Cast< IPlayerStateInterface>(TryGetPawnOwner());
	if (PlayerState)
	{
		Stat = PlayerState->GetMyStatComponent();
	}
}

void UAnimInstance_Countess::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character)
	{
		Speed = Character->GetVelocity().Size();
		Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
		IsCrouched = Character->bIsCrouched;
		IsFalling = Character->GetMovementComponent()->IsFalling();
	}

	// 플레이어 추가 상태
	IPlayerStateInterface* PlayerState = Cast< IPlayerStateInterface>(TryGetPawnOwner());
	if (PlayerState)
	{
		IsDoubleJump = PlayerState->GetIsDoubleJumping();
		WeaponIdx = PlayerState->GetCurrentWeaponIndex();
		IsOnWall = PlayerState->GetIsOnWall();
		IsClimbingUp = PlayerState->GetIsClibmingUp();
		IsDeath = PlayerState->GetIsDeath();
	}
}

void UAnimInstance_Countess::PlayDefaultAttackMontage()
{
	Montage_Play(AttackMontage_Default, 1.f);
}

void UAnimInstance_Countess::PlayAttackMontage()
{
	Montage_Play(AttackMontage_SwordDefault, 1.f);
}

void UAnimInstance_Countess::PlayAttackMontageQ()
{
	Montage_Play(AttackMontage_Q, 1.f);
}

void UAnimInstance_Countess::PlayAttackMontageE()
{
	Montage_Play(AttackMontage_E, 1.f);
}

void UAnimInstance_Countess::PlayAttackMontageR()
{
	Montage_Play(AttackMontage_R, 1.f);
}

void UAnimInstance_Countess::PlayBowAttackMontage()
{
	Montage_Play(BowAttackMontage, 1.f);
}

void UAnimInstance_Countess::JumpToSection_Default(int32 SectionIndex)
{
}

void UAnimInstance_Countess::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontage_SwordDefault);
}

FName UAnimInstance_Countess::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UAnimInstance_Countess::PlayClimbingComplete()
{
	Montage_Play(ClimbingCompleteMontage, 1.f);
}

void UAnimInstance_Countess::AnimNotify_AttackHit()
{

}

void UAnimInstance_Countess::AnimNotify_AttackHit_Q()
{
	if (Stat)
	{
		TraceDistance = Stat->GetTotalStat().AttackRange * 300.f;
		OnAttackHit_Q.Broadcast(Stat->GetTotalStat().AttackQ, TraceDistance);
	}
}

void UAnimInstance_Countess::AnimNotify_AttackHit_E()
{
	if (Stat)
	{
		TraceDistance = Stat->GetTotalStat().AttackRange * 500.f;
		OnAttackHit_E.Broadcast(Stat->GetTotalStat().AttackE, TraceDistance);
	}
}

void UAnimInstance_Countess::AnimNotify_AttackHit_R()
{
	if (Stat)
	{
		TraceDistance = Stat->GetTotalStat().AttackRange * 700.f;
		OnAttackHit_R.Broadcast(Stat->GetTotalStat().AttackR, TraceDistance);
	}
}

