// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy_Boss.h"
#include "Kismet/GameplayStatics.h"
#include "Components/MyStatComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/EnemyHPWidget.h"
#include "AI/AIController_Enemy.h"
#include "Enemies/Enemy_AnimInstance.h"
#include "Characters/Character_Parent.h"
#include "GameData/CharacterEnum.h"
#include "GameData/GameCollision.h"


AEnemy_Boss::AEnemy_Boss()
{
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightWeaponMesh"));
	WeaponLeft = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftWeaponMesh"));
	Weapon->SetupAttachment(GetMesh());
	WeaponLeft->SetupAttachment(GetMesh());

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordMeshLeft(TEXT("SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Sword/enemy_Sword_Mesh.enemy_Sword_Mesh'"));
	if (SwordMeshLeft.Succeeded())
	{
		Weapon->SetSkeletalMesh(SwordMeshLeft.Object);
		WeaponLeft->SetSkeletalMesh(SwordMeshLeft.Object);
	}

	Level = 5;
	EnemyExp = 100;
	AttackRange = 700.f;
	AttackRadius = 300.f;
	
}

void AEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();

	if (Weapon)
	{
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SwordSocket"));
	}
	if (WeaponLeft)
	{
		WeaponLeft->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("LeftSwordSocket"));
	}
}

void AEnemy_Boss::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->SetLevelStat(Level);

	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AEnemy_Boss::OnAttackMontageEnded);
		AnimInstance->OnBossAttackHit.AddUObject(this, &AEnemy_Boss::AttackCheck);
		AnimInstance->OnSkillAttack.AddUObject(this, &AEnemy_Boss::SkillAttack);
	}

	HpBar->InitWidget();

	auto EnemyWidget = Cast<UEnemyHPWidget>(HpBar->GetUserWidgetObject());
	if (EnemyWidget)
	{
		EnemyWidget->BindHp(Stat);
		EnemyWidget->BindLevel(Level);
	}
	
}

void AEnemy_Boss::Attack()
{
	Super::Attack();

	if (IsAttacking || Stat->GetCurrentHp() <= 0.f)
		return;

	IsAttacking = true;

	// ü���� �� �Ʒ��� �������� ����
	if (Stat->GetHpRatio() < 0.5f && !JumpAttacking)
	{
		Jump();
		FVector Location = GetActorLocation();
		Location.Z += 200.f;
		SetActorLocation(Location);
		JumpAttacking = true;
	}

	AnimInstance->PlayAttackMontage_Boss();
	AnimInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % 4;
}

void AEnemy_Boss::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + GetActorForwardVector() * AttackRange;

	bool bResult = GetWorld()->SweepSingleByChannel(HitResult, TraceStart, TraceEnd,
		FQuat::Identity,ATTACK, FCollisionShape::MakeSphere(AttackRadius), Params);

	if (bResult)
	{
		ACharacter_Parent* Player = Cast<ACharacter_Parent>(HitResult.Actor);
		if (Player)
		{
			FDamageEvent DamageEvent;
			Player->TakeDamage(Stat->GetTotalStat().Attack, DamageEvent, GetController(), this);
		}
	}
}

void AEnemy_Boss::SkillAttack()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	
	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 1500.f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(300.f),
		Params);

	if (bResult)
	{
		ACharacter_Parent* Player = Cast<ACharacter_Parent>(HitResult.Actor);
		if (Player)
		{
			FDamageEvent DamageEvent;
			Player->TakeDamage(Stat->GetTotalStat().Attack, DamageEvent, GetController(), this);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillEffect, Player->GetTransform());
		}
	}

}

void AEnemy_Boss::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	FTransform Transform(FRotator::ZeroRotator, Hit.ImpactPoint,FVector(10.f,10.f,10.f));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), JumpEffect, Transform);

	if (AttackedCamShake)
	{
		OnBossJump.Broadcast(AttackedCamShake);
	}
}

void AEnemy_Boss::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

bool AEnemy_Boss::IsBossEnemyDead()
{
	return IsPawnControlled();
}
