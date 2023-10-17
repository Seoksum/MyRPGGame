// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Character_Greystone.h"
#include "Characters/Character_Parent.h"
#include "Characters/AnimInstance_Greystone.h"
#include "UI/InGame.h"
#include "Components/TextBlock.h"
#include "Components/MyStatComponent.h"
#include "Components/InventoryComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "UI/HPWidget.h"
#include "Camera/CameraComponent.h"
#include "Enemies/Enemy.h"
#include "Items/WeaponItemDataAsset_Sword.h"
#include "GameData/GameCollision.h"
#include "GameData/CharacterEnum.h"


ACharacter_Greystone::ACharacter_Greystone()
{


}

void ACharacter_Greystone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Attack_Q"), EInputEvent::IE_Pressed, this, &ACharacter_Greystone::AttackQ);
	PlayerInputComponent->BindAction(TEXT("Attack_E"), EInputEvent::IE_Pressed, this, &ACharacter_Greystone::AttackE);
	PlayerInputComponent->BindAction(TEXT("Attack_R"), EInputEvent::IE_Pressed, this, &ACharacter_Greystone::AttackR);

}

void ACharacter_Greystone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 벽 위를 더 이상 오를 수 없어 착지해야할 때
	if (bIsClimbingComplete)
	{
		SetActorLocation(GetActorLocation() + GetActorForwardVector() * 3.f);
		SetActorLocation(GetActorLocation() + GetActorUpVector() * 10.f);
	}

	if (bIsClimbingUp && bIsOnWall)
	{
		FVector Loc = GetActorLocation();
		SetActorLocation(FVector(Loc.X, Loc.Y, Loc.Z + 1.1f));
	}

	if (AttackMoving)
	{
		FVector NewLocation1 = GetActorLocation() + GetActorForwardVector() * 7.f;
		SetActorLocation(NewLocation1);
	}
}

void ACharacter_Greystone::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->HideBoneByName(TEXT("sword_bottom"), EPhysBodyOp::PBO_None);

	Mana = Stat->GetTotalStat().Mana;
}

void ACharacter_Greystone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UAnimInstance_Greystone>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnAttackHit_Q.AddUObject(this, &ACharacter_Greystone::SkillAttackCheck);
		AnimInstance->OnAttackHit_E.AddUObject(this, &ACharacter_Greystone::SkillAttackCheck);
		AnimInstance->OnAttackHit_R.AddUObject(this, &ACharacter_Greystone::SkillAttackCheck);

		AnimInstance->OnMontageEnded.AddDynamic(this, &ACharacter_Greystone::OnAttackMontageEnded);
		AnimInstance->OnCameraShake.AddUObject(this, &ACharacter_Greystone::CameraShakeCheck);

	}
}

void ACharacter_Greystone::Attack()
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

	if (CurrentWeaponIndex == EWeapon::Sword)
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

void ACharacter_Greystone::AttackQ()
{
	if (CurrentWeaponIndex != EWeapon::Sword || IsAttackingQ || Stat->GetCurrentMana() < 0.f)
		return;

	IsAttackingQ = true;
	AnimInstance->PlayAttackMontageQ();
	Stat->OnAttacking(Mana); //Mana 크기만큼 플레이어의 마나 소모
	Remaining_SkillQ = 3;
	GetWorldTimerManager().SetTimer(QSkillHandle, this, &ACharacter_Greystone::EndAttack_Q, 1.f, true);
}

void ACharacter_Greystone::AttackE()
{
	if (CurrentWeaponIndex != EWeapon::Sword || IsAttackingE || Stat->GetCurrentMana() < 0.f)
		return;

	IsAttackingE = true;
	AnimInstance->PlayAttackMontageE();
	Remaining_SkillE = 6;

	Stat->OnAttacking(Mana + 5);
	GetWorldTimerManager().SetTimer(ESkillHandle, this, &ACharacter_Greystone::EndAttack_E, 1.f, true);
}

void ACharacter_Greystone::AttackR()
{
	if (CurrentWeaponIndex != EWeapon::Sword || IsAttackingR || Stat->GetCurrentMana() < 0.f)
		return;

	IsAttackingR = true;
	AttackMoving = true;
	Remaining_SkillR = 10;

	AnimInstance->PlayAttackMontageR();

	Stat->OnAttacking(Mana + 10);
	GetWorldTimerManager().SetTimer(RSkillHandle, this, &ACharacter_Greystone::EndAttack_R, 1.f, true);
}

void ACharacter_Greystone::SkillAttackCheck(int32 damage, float TraceDistance, class UParticleSystem* Particle)
{
	if (CurrentWeaponIndex == EWeapon::Sword)
	{
		TArray<FHitResult> TraceHits;

		const FVector TraceStart = GetActorLocation();
		const FVector TraceEnd = TraceStart + (GetActorForwardVector() * TraceDistance);
		FCollisionShape SweepShape = FCollisionShape::MakeSphere(100.0f);

		bool bResult = GetWorld()->SweepMultiByChannel(TraceHits, TraceStart, TraceEnd, FQuat::Identity, ATTACK, SweepShape);
		if (bResult)
		{
			for (FHitResult& Hit : TraceHits)
			{
				FDamageEvent DamageEvent;
				Hit.Actor->TakeDamage(Stat->GetTotalStat().Attack, DamageEvent, GetController(), this);
				if (Particle)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Hit.Actor->GetTransform());
				}
			}
		}
	}
}

void ACharacter_Greystone::PressClimbingUp()
{
	Super::PressClimbingUp();

	if (bIsOnWall)
	{
		if (bIsClimbingUp && CanPressClimbingUp)
		{
			float Duration = AnimInstance->PlayClimbing();
			CanPressClimbingUp = false;
			GetWorld()->GetTimerManager().SetTimer(ClimbingTimerHandle, this, &ACharacter_Greystone::ReleaseClimbing, Duration - 0.6f, true);
		}
	}
	
	else
	{
		if (bIsClimbingComplete)
		{
			AnimInstance->PlayClimbingComplete();
			
		}
	}
}

void ACharacter_Greystone::ReleaseClimbing()
{
	bIsClimbingUp = false;
	CanPressClimbingUp = true;
	bIsClimbingComplete = false;
	GetWorld()->GetTimerManager().ClearTimer(ClimbingTimerHandle);
}

void ACharacter_Greystone::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	AttackMoving = false;

}

void ACharacter_Greystone::CameraShakeCheck()
{
	Super::CameraShakeCheck();
	AttackMoving = false;
}

void ACharacter_Greystone::AddInGameWidget(class UInGame* InGame)
{
	Super::AddInGameWidget(InGame);
	if (InGame)
	{
		InGame->SetGreystone(Level);
	}
}