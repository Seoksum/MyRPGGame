// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy_Corpse.h"
#include "Kismet/GameplayStatics.h"
#include "Enemies/Enemy_AnimInstance.h"
#include "Components/MyStatComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/EnemyHPWidget.h"
#include "Characters/Character_Parent.h"
#include "GameData/CharacterEnum.h"
#include "GameData/GameCollision.h"


AEnemy_Corpse::AEnemy_Corpse()
{
	// Skeletal Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse/Corpse_Sword.Corpse_Sword'"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}
	GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));

	// Weapon Mesh
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	Weapon->SetupAttachment(GetMesh());
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordMesh(TEXT("SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Sword/enemy_Sword_Mesh.enemy_Sword_Mesh'"));
	if (SwordMesh.Succeeded())
	{
		Weapon->SetSkeletalMesh(SwordMesh.Object);
	}
	Weapon->SetCollisionProfileName(FName("NoCollision"));

	Level = 2;
	EnemyExp = 15;
	AttackRange = 500.f;
	AttackRadius = 300.f;
	
}

void AEnemy_Corpse::BeginPlay()
{
	Super::BeginPlay();


}

void AEnemy_Corpse::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (Weapon)
	{
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SwordSocket"));
	}

	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AEnemy_Corpse::OnAttackMontageEnded);
		AnimInstance->OnCorpseAttackHit.AddUObject(this, &AEnemy_Corpse::AttackCheck);
	}

	HpBar->InitWidget();

	auto EnemyWidget = Cast<UEnemyHPWidget>(HpBar->GetUserWidgetObject());
	if (EnemyWidget)
	{
		EnemyWidget->BindHp(Stat);
		EnemyWidget->BindLevel(Level);
	}

}

void AEnemy_Corpse::Attack()
{
	Super::Attack();
	
	if (IsAttacking|| Stat->GetCurrentHp() <= 0.f)
		return;

	AnimInstance->PlayAttackMontage_Corpse();
	IsAttacking = true;

}

void AEnemy_Corpse::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	Params.AddIgnoredActor(this);

	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + GetActorForwardVector() * AttackRange;

	bool bResult = GetWorld()->LineTraceSingleByChannel(OUT HitResult, TraceStart, TraceEnd, ATTACK, Params);

	if (bResult)
	{
		ACharacter_Parent* Player = Cast<ACharacter_Parent>(HitResult.Actor);

		if (Player)
		{
			if (Player->bIsCrouched)
				return;
			FDamageEvent DamageEvent;
			Player->TakeDamage(Stat->GetTotalStat().Attack, DamageEvent, GetController(), this);
		}
	}
}

void AEnemy_Corpse::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}



