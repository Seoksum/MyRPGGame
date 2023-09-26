// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/Character_Parent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemyProjectile::AEnemyProjectile()
{

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(35.f);
	CollisionComp->SetCollisionProfileName(FName("Enemy"));
	CollisionComp->SetSimulatePhysics(true);
	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->OnComponentHit.AddDynamic(this, &AEnemyProjectile::OnHit);
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp; // ProjectileMovement가 이동을 위해 액터의 루트 컴포넌트를 사용한다
	ProjectileMovement->SetUpdatedComponent(CollisionComp);
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform); // World Transform 유지
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/ParagonMinions/FX/Meshes/PlayerBuffs/SM_Buff_Sphere.SM_Buff_Sphere'"));
	if (SM.Succeeded())
	{
		MeshComp->SetStaticMesh(SM.Object);
	}

	BaseDamage = 15.f;
	InitialLifeSpan = 2.f;
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (AttackEffect)
	{
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AttackEffect,GetActorTransform());
		UGameplayStatics::SpawnEmitterAttached(AttackEffect, MeshComp);
	}

}


void AEnemyProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ACharacter* Player = Cast<ACharacter>(OtherActor);
	FDamageEvent DamageEvent;
	if (Player)
	{
		Player->TakeDamage(BaseDamage, DamageEvent, GetInstigatorController(), GetOwner());
	}

}

