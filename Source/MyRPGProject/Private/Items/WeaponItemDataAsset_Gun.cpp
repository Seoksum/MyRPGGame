// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponItemDataAsset_Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "TimerManager.h"
#include "Characters/Character_Parent.h"
#include "Enemies/Enemy.h"
#include "TimerManager.h"
#include "GameData/GameCollision.h"


// Sets default values
UWeaponItemDataAsset_Gun::UWeaponItemDataAsset_Gun()
{
	MuzzleSocketName = "MuzzleFlashSocket";
	TracerTargetName = "Target";

	BaseDamage = 20.f;
	RateOfFire = 600.f; // �� �� 60�� �Ѿ�
	TimeBetweenShots = 60.f / RateOfFire; // �� �� 10�� 
	WeaponMeshComponent = WeaponMesh.Get();
}

void UWeaponItemDataAsset_Gun::Fire()
{
	if (Player)
	{
		FHitResult Hit;
		FVector EyeLocation;
		FRotator EyeRotation;
		Player->GetActorEyesViewPoint(EyeLocation, EyeRotation); // OUT parameter
		
		FVector TraceStart = WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = TraceStart + (ShotDirection * 3000); // ���� ����
		FVector TraceEndPoint = TraceEnd;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Player);

		bool bHit = Player->GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ATTACK, QueryParams);
		if (bHit)
		{
			AEnemy* Enemy = Cast<AEnemy>(Hit.GetActor());
			if (Enemy)
			{
				FDamageEvent DamageEvent;
				Enemy->TakeDamage(BaseDamage, DamageEvent, Player->GetInstigatorController(), Player);
				PlayImpactEffects(Hit.ImpactPoint, BloodImpactEffect);
			}
			else
			{
				PlayImpactEffects(Hit.ImpactPoint, DefaultImpactEffect);
			}

			TraceEndPoint = Hit.ImpactPoint;
		}

		PlayFireEffects(TraceEndPoint);
		LastFiredTime = Player->GetWorld()->TimeSeconds;
	}
}

void UWeaponItemDataAsset_Gun::WeaponAttack(ACharacter_Parent* InPlayer)
{
	Super::WeaponAttack(Player);

	Player = InPlayer;
	StartFire();
	
}

void UWeaponItemDataAsset_Gun::StartFire()
{
	if (WeaponMeshComponent != nullptr)
	{
		float FirstDelay = FMath::Max(LastFiredTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.f);
		Player->GetWorld()->GetTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &UWeaponItemDataAsset_Gun::Fire, TimeBetweenShots, true, 0.f);
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Player->GetActorLocation());
	}
}

void UWeaponItemDataAsset_Gun::StopFire()
{
	Player->GetWorld()->GetTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}

void UWeaponItemDataAsset_Gun::PlayFireEffects(FVector TraceEndPoint)
{
	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, WeaponMeshComponent.Get(), MuzzleSocketName);
	}

	if (TracerEffect)
	{
		// TracerEffect�� 'P_SmokeTrail'�ε� �� ��ƼŬ�ý����� �����ϱ� ���ؼ��� Source�� Target �κ��� �ִ�. 
		FVector MuzzleLocation = WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
		UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(Player->GetWorld(), TracerEffect, MuzzleLocation);
		if (TracerComp)
		{
			TracerComp->SetVectorParameter(TracerTargetName, TraceEndPoint); // P_SmokeTrail�� Target���� Target Name�� ã�� ���ڷ� �ִ´�.
		}
	}

	if (Player)
	{
		Player->CameraShake(FireCamShake);
	}
}

void UWeaponItemDataAsset_Gun::PlayImpactEffects(FVector ImpactPoint, UParticleSystem* Particle)
{
	if (Particle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(Player->GetWorld(), Particle, ImpactPoint);
	}
}
