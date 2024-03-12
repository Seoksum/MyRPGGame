// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon_Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
//#include "TimerManager.h"
#include "Characters/Character_Parent.h"
#include "Enemies/Enemy.h"
#include "GameData/GameCollision.h"


// Sets default values
AWeapon_Gun::AWeapon_Gun()
{
	SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));

	MuzzleSocketName = "MuzzleFlashSocket";
	TracerTargetName = "Target";

	BaseDamage = 20.f;
	RateOfFire = 600.f; // �� �� 60�� �Ѿ�
	TraceDistance = 2000.f;
}

// Called when the game starts or when spawned
void AWeapon_Gun::BeginPlay()
{
	Super::BeginPlay();

	TimeBetweenShots = 60.f / RateOfFire;
}

void AWeapon_Gun::Attack()
{
	Super::Attack();
	
	ACharacter_Parent* MyOwner = Cast<ACharacter_Parent>(GetOwner());
	if (MyOwner)
	{
		FHitResult Hit;
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation); // OUT parameter

		FVector TraceStart = MyOwner->WeaponSkeletalMeshComp->GetSocketLocation(MuzzleSocketName);
		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = TraceStart + (ShotDirection * TraceDistance); // ���� ����
		FVector TraceEndPoint = TraceEnd;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(MyOwner);

		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ATTACK, QueryParams);
		if (bHit)
		{
			AEnemy* Enemy = Cast<AEnemy>(Hit.GetActor());
			TraceEndPoint = Hit.ImpactPoint;
			if (Enemy)
			{
				FDamageEvent DamageEvent;
				Enemy->TakeDamage(BaseDamage, DamageEvent, MyOwner->GetInstigatorController(), this);
				PlayImpactEffects(TraceEndPoint, BloodImpactEffect);
			}
			else
			{
				PlayImpactEffects(TraceEndPoint, DefaultImpactEffect);
			}
		}
		PlayFireEffects(TraceEndPoint);
		LastFiredTime = GetWorld()->TimeSeconds; // ������ �߻� �ð��� ���(World�� time)
	}
}

void AWeapon_Gun::StartFire()
{
	float FirstDelay = FMath::Max(LastFiredTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.f);
	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &AWeapon_Gun::Attack, TimeBetweenShots, true, FirstDelay);
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
}

void AWeapon_Gun::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}

void AWeapon_Gun::PlayFireEffects(FVector TraceEndPoint)
{
	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, RootComponent, MuzzleSocketName);
	}

	ACharacter_Parent* MyOwner = Cast<ACharacter_Parent>(GetOwner());
	if (MyOwner)
	{
		if (TracerEffect)
		{
			// TracerEffect�� 'P_SmokeTrail'�ε� �� ��ƼŬ�ý����� �����ϱ� ���ؼ��� Source�� Target �κ��� �ִ�. 
			FVector MuzzleLocation = MyOwner->WeaponSkeletalMeshComp->GetSocketLocation(MuzzleSocketName);
			UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);
			if (TracerComp)
			{
				TracerComp->SetVectorParameter("Target", TraceEndPoint); // P_SmokeTrail�� Target���� Target Name�� ã�� ���ڷ� �ִ´�.
			}
		}
		MyOwner->CameraShake(FireCamShake);
	}
}

void AWeapon_Gun::PlayImpactEffects(FVector ImpactPoint, UParticleSystem* Particle)
{
	if (Particle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, ImpactPoint);
	}
}
