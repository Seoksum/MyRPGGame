// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AnimInstance_Greystone.h"
#include "Characters/Character_Greystone.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/MyStatComponent.h"



UAnimInstance_Greystone::UAnimInstance_Greystone()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_DefaultAttack(TEXT("AnimMontage'/Game/MainCharacter/Greystone/Montages/Attack_Default.Attack_Default'"));
	if (Montage_DefaultAttack.Succeeded())
	{
		AttackMontage_Default = Montage_DefaultAttack.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_SwordDefaultAttack(TEXT("AnimMontage'/Game/MainCharacter/Greystone/Montages/Attack_SwordDefault.Attack_SwordDefault'"));
	if (Montage_SwordDefaultAttack.Succeeded())
	{
		AttackMontage_SwordDefault = Montage_SwordDefaultAttack.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_AttackQ(TEXT("AnimMontage'/Game/MainCharacter/Greystone/Montages/Attack_SwordQ.Attack_SwordQ'"));
	if (Montage_AttackQ.Succeeded())
	{
		AttackMontage_Q = Montage_AttackQ.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_AttackE(TEXT("AnimMontage'/Game/MainCharacter/Greystone/Montages/Attack_SwordE.Attack_SwordE'"));
	if (Montage_AttackE.Succeeded())
	{
		AttackMontage_E = Montage_AttackE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_AttackR(TEXT("AnimMontage'/Game/MainCharacter/Greystone/Montages/Attack_SwordR.Attack_SwordR'"));
	if (Montage_AttackR.Succeeded())
	{
		AttackMontage_R = Montage_AttackR.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_Climbing(TEXT("AnimMontage'/Game/MainCharacter/Greystone/Montages/ClimbingComplete.ClimbingComplete'"));
	if (Montage_Climbing.Succeeded())
	{
		ClimbingCompleteMontage = Montage_Climbing.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_Bow(TEXT("AnimMontage'/Game/MainCharacter/Greystone/Montages/Bow_AttackDefault.Bow_AttackDefault'"));
	if (Montage_Bow.Succeeded())
	{
		BowAttackMontage = Montage_Bow.Object;
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

	//auto Pawn = TryGetPawnOwner();  // //나를 소유하고 있는 Pawn 
	//if (IsValid(Pawn))
	//{
	//	auto PlayerCharacter = Cast<ACharacter_Greystone>(Pawn);
	//	if (PlayerCharacter)
	//	{
	//		Speed = PlayerCharacter->GetVelocity().Size();
	//		Direction = CalculateDirection(PlayerCharacter->GetVelocity(), PlayerCharacter->GetActorRotation());
	//		IsFalling = PlayerCharacter->GetMovementComponent()->IsFalling();
	//		IsDoubleJump = PlayerCharacter->IsDoubleJumping;
	//		WeaponIdx = PlayerCharacter->CurrentWeaponIndex;
	//		IsOnWall = PlayerCharacter->bIsOnWall;
	//		IsClimbingUp = PlayerCharacter->bIsClimbingUp;
	//		IsCrouched = PlayerCharacter->bIsCrouched;
	//		IsDeath = PlayerCharacter->IsDeath;
	//	}
	//}

	// 플레이어 기본 제공 상태
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

void UAnimInstance_Greystone::PlayClimbingComplete()
{
	Montage_Play(ClimbingCompleteMontage, 1.f);
}

void UAnimInstance_Greystone::AnimNotify_AttackHit()
{
	//auto Player = Cast<ACharacter_Greystone>(TryGetPawnOwner());
	//if (Player)
	//{
	//	auto Stat = Player->GetMyStatComponent();
	//	if (Stat)
	//	{
	//		TraceDistance = 150.f;
	//		OnAttackHit.Broadcast(Stat->GetTotalStat().Attack, TraceDistance, nullptr);
	//	}
	//}
}

void UAnimInstance_Greystone::AnimNotify_AttackHit_Q()
{
	if (Stat)
	{
		TraceDistance = 200.f;
		OnAttackHit_Q.Broadcast(Stat->GetTotalStat().AttackQ, TraceDistance, AttackQ_Effect);
	}
}

void UAnimInstance_Greystone::AnimNotify_AttackHit_E()
{
	if (Stat)
	{
		TraceDistance = 300.f;
		OnAttackHit_E.Broadcast(Stat->GetTotalStat().AttackE, TraceDistance, AttackE_Effect);
	}

}

void UAnimInstance_Greystone::AnimNotify_AttackHit_R()
{
	//auto Player = Cast<ACharacter_Greystone>(TryGetPawnOwner());
	//if (Player)
	//{
	//	auto Stat = Player->GetMyStatComponent();
	//	if (Stat)
	//	{
	//		TraceDistance = 400.f;
	//		OnAttackHit_R.Broadcast(Stat->GetTotalStat().AttackR, TraceDistance, nullptr);
	//	}
	//}

	if (Stat)
	{
		TraceDistance = 400.f;
		OnAttackHit_R.Broadcast(Stat->GetTotalStat().AttackR, TraceDistance, nullptr);
	}
}

void UAnimInstance_Greystone::AnimNotify_CamShakeHit()
{
	OnCameraShake.Broadcast();
}

