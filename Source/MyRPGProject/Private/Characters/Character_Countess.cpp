// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Character_Countess.h"
#include "Characters/AnimInstance_Countess.h"
#include "UI/InGame.h"
#include "Components/TextBlock.h"
#include "Components/MyStatComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "UI/HPWidget.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Enemies/Enemy.h"
#include "GameData/CharacterEnum.h"


ACharacter_Countess::ACharacter_Countess()
{
	LeftSword = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftSword"));

	TotalAttackIndex = 2;
	Level = 1;

}

void ACharacter_Countess::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Attack_Q"), EInputEvent::IE_Pressed, this, &ACharacter_Countess::AttackQ);
	PlayerInputComponent->BindAction(TEXT("Attack_E"), EInputEvent::IE_Pressed, this, &ACharacter_Countess::AttackE);
	PlayerInputComponent->BindAction(TEXT("Attack_R"), EInputEvent::IE_Pressed, this, &ACharacter_Countess::AttackR);
}

void ACharacter_Countess::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsClimbingComplete)
	{
		SetActorLocation(GetActorLocation() + GetActorForwardVector() * 3.f);
		SetActorLocation(GetActorLocation() + GetActorUpVector() * 7.f);
	}
}



void ACharacter_Countess::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	GetMesh()->HideBoneByName(TEXT("weapon_l"), EPhysBodyOp::PBO_None);

	/*Sword_L = GetWorld()->SpawnActor<AWeapon_Sword>(SwordClass);

	if (Sword && Sword_L)
	{
		Sword_L->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket_L"));
		Sword_L->SetOwner(this);
	}*/



}

void ACharacter_Countess::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UAnimInstance_Countess>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &ACharacter_Countess::OnAttackMontageEnded);
		AnimInstance->OnAttackHit.AddUObject(this, &ACharacter_Countess::AttackCheck);
		AnimInstance->OnAttackHit_Q.AddUObject(this, &ACharacter_Countess::AttackCheck);
		AnimInstance->OnAttackHit_E.AddUObject(this, &ACharacter_Countess::AttackCheck);
		AnimInstance->OnAttackHit_R.AddUObject(this, &ACharacter_Countess::AttackCheck);
	}

}

void ACharacter_Countess::Attack()
{
	Super::Attack();

	if (IsAttacking)
		return;

	if (CurrentWeaponIndex == EWeapon::None)
	{
		AnimInstance->PlayDefaultAttackMontage();
		AnimInstance->JumpToSection_Default(AttackIndex);
		AttackIndex = (AttackIndex + 1) % TotalAttackIndex;
		IsAttacking = true;
	}

	else if (CurrentWeaponIndex == EWeapon::Sword)
	{
		AnimInstance->PlayAttackMontage();
		AnimInstance->JumpToSection(AttackIndex);
		AttackIndex = (AttackIndex + 1) % TotalAttackIndex;
		IsAttacking = true;
	}

	else if (CurrentWeaponIndex == EWeapon::Bow)
	{
		AnimInstance->PlayBowAttackMontage();
		IsAttacking = true;
	}
}

void ACharacter_Countess::AttackQ()
{
	if (CurrentWeaponIndex != EWeapon::Sword || IsAttackingQ || Stat->GetCurrentMana() < 0.f)
		return;

	AnimInstance->PlayAttackMontageQ();
	IsAttackingQ = true;

	Remaining_SkillQ = 3;

	Stat->OnAttacking(Mana);

	GetWorldTimerManager().SetTimer(QSkillHandle, this, &ACharacter_Countess::EndAttack_Q, 1.f, true);
}

void ACharacter_Countess::AttackE()
{
	if (CurrentWeaponIndex != EWeapon::Sword || IsAttackingE || Stat->GetCurrentMana() < 0.f)
		return;

	IsAttackingE = true;
	AnimInstance->PlayAttackMontageE();
	Remaining_SkillE = 6;

	Stat->OnAttacking(Mana + 5);
	GetWorldTimerManager().SetTimer(ESkillHandle, this, &ACharacter_Countess::EndAttack_E, 1.f, true);
}

void ACharacter_Countess::AttackR()
{
	if (CurrentWeaponIndex != EWeapon::Sword || IsAttackingR || Stat->GetCurrentMana() < 0.f)
		return;

	IsAttackingR = true;
	AnimInstance->PlayAttackMontageR();

	Remaining_SkillR = 10;

	Stat->OnAttacking(Mana + 10);
	GetWorldTimerManager().SetTimer(RSkillHandle, this, &ACharacter_Countess::EndAttack_R, 1.f, true);
}



void ACharacter_Countess::AttackCheck(int32 damage, float TraceDistance)
{
	//float TraceDistance = 300.f;
	TArray<FHitResult> TraceHits;
	FVector CameraFwVector = Camera->GetForwardVector();
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + (CameraFwVector * TraceDistance); // 1000.0f
	FCollisionShape SweepShape = FCollisionShape::MakeSphere(200.0f);


	bool bResult = GetWorld()->SweepMultiByChannel(TraceHits, TraceStart, TraceEnd, FQuat::Identity, ECC_GameTraceChannel3, SweepShape);
	if (bResult)
	{
		for (FHitResult& Hit : TraceHits)
		{
			AEnemy* Enemy = Cast<AEnemy>(Hit.Actor);
			if (Enemy && !Enemy->IsDeath)
			{
				FDamageEvent DamageEvent;
				Enemy->TakeDamage(damage, DamageEvent, GetController(), this);
			}
		}
	}
}

void ACharacter_Countess::PressClimbingUp()
{
	Super::PressClimbingUp();
	if (!bIsOnWall && bIsClimbingComplete)
	{
		AnimInstance->PlayClimbingComplete();
	}
}

void ACharacter_Countess::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;

}


void ACharacter_Countess::AddInGameWidget(class UInGame* InGame)
{
	Super::AddInGameWidget(InGame);
	if (InGame)
	{
		InGame->SetCountess(Level);
	}
}

void ACharacter_Countess::SetupPlayerView(FVector Location, FVector SocketOffset)
{
	Super::SetupPlayerView(Location, SocketOffset);

	if (CurrentWeaponIndex == EWeapon::Sword)
	{
		LeftSword->SetSkeletalMesh(Weapon->SkeletalMesh);
		LeftSword->SetVisibility(true);
		LeftSword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("SwordSocket_L"));
	}
	else
	{
		LeftSword->SetVisibility(false);
	}


}