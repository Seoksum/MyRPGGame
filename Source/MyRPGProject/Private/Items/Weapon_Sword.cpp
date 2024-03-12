// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon_Sword.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Character_Parent.h"
#include "GameData/GameCollision.h"

// Sets default values
AWeapon_Sword::AWeapon_Sword()
{

	Radius = 200.f;
}

// Called when the game starts or when spawned
void AWeapon_Sword::BeginPlay()
{
	Super::BeginPlay();

}

void AWeapon_Sword::Attack(int32 damage, float TraceDistance, UParticleSystem* Particle)
{
	Super::Attack(damage, TraceDistance, Particle);
	
	ACharacter_Parent* MyOwner = Cast<ACharacter_Parent>(GetOwner());
	if (MyOwner)
	{
		TArray<FHitResult> TraceHits;
		FVector TraceStart = MyOwner->GetActorLocation();
		FVector TraceEnd = TraceStart + (MyOwner->GetActorForwardVector() * TraceDistance); 
		FCollisionShape SweepShape = FCollisionShape::MakeSphere(Radius);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(MyOwner);
		
		bool bResult = GetWorld()->SweepMultiByChannel(TraceHits, TraceStart, TraceEnd, 
			FQuat::Identity, ATTACK, SweepShape, QueryParams);
		if (bResult)
		{
			for (FHitResult& Hit : TraceHits)
			{
				FDamageEvent DamageEvent;
				Hit.Actor->TakeDamage(damage, DamageEvent, MyOwner->GetController(), this);
				if (Particle)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Hit.Actor->GetTransform());
				}
			}
		}
	}
}




