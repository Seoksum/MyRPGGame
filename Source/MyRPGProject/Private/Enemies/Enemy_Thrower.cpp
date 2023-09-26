// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy_Thrower.h"
#include "Kismet/GameplayStatics.h"
#include "Components/MyStatComponent.h"
#include "Enemies/Enemy_AnimInstance.h"
#include "Components/WidgetComponent.h"
#include "UI/EnemyHPWidget.h"
#include "Enemies/EnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameData/CharacterEnum.h"


AEnemy_Thrower::AEnemy_Thrower()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Hooker/Hooker_Mesh.Hooker_Mesh'"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	Level = 1;
	EnemyExp = 10;
	EnemyIndex = EEnemy::SkeletonEnemy;
}

void AEnemy_Thrower::BeginPlay()
{
	Super::BeginPlay();


}

void AEnemy_Thrower::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AEnemy_Thrower::OnAttackMontageEnded);
		AnimInstance->OnThrowProjectile.AddUObject(this, &AEnemy_Thrower::ThrowProjectile);
	}

	HpBar->InitWidget();
	auto EnemyWidget = Cast<UEnemyHPWidget>(HpBar->GetUserWidgetObject());
	if (EnemyWidget)
	{
		EnemyWidget->BindHp(Stat);
		EnemyWidget->BindLevel(Level);
	}

}

void AEnemy_Thrower::Attack()
{
	Super::Attack();

	if (IsAttacking || Stat->GetCurrentHp() <= 0.f)
		return;

	AnimInstance->PlayAttackMontage_Thrower();
	IsAttacking = true;

}

void AEnemy_Thrower::ThrowProjectile()
{
	// 플레이어를 인식한 후 그 곳을 향해 던지기
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	if (Player == nullptr)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	FVector SpawnLocation = GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
	FRotator SpawnRotation = GetActorForwardVector().Rotation();
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);
	
	Projectile = GetWorld()->SpawnActor<AEnemyProjectile>(ProjectileClass, SpawnTransform);
	FVector NewFOV = FMath::VInterpTo(Projectile->GetActorLocation(), Player->GetActorLocation(), GetWorld()->DeltaTimeSeconds, 20.f);
	Projectile->SetActorLocation(NewFOV);
}

void AEnemy_Thrower::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

