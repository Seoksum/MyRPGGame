// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon_Bow.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "TimerManager.h"
#include "Items/Arrow.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/Character_Parent.h"


AWeapon_Bow::AWeapon_Bow()
{

	//SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	//RootComponent = MeshComp;
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Weapon/Archer/Archer_Bow_Weapon.Archer_Bow_Weapon'"));
	//if (SM.Succeeded())
	//{
	//	SkeletalMeshComp->SetSkeletalMesh(SM.Object);
	//}

	SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));

	ArrowSpeedVal = 4000.f;
}

// Called when the game starts or when spawned
void AWeapon_Bow::BeginPlay()
{
	Super::BeginPlay();

}

void AWeapon_Bow::Attack()
{
	Super::Attack();

	ACharacter_Parent* MyOwner = Cast<ACharacter_Parent>(GetOwner());

	if (MyOwner)
	{
		FVector SpawnLocation = MyOwner->WeaponSkeletalMeshComp->GetSocketLocation(FName("ArrowSocket"));
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation); // OUT parameter
		FRotator SpawnRotation = EyeRotation;
		FTransform SpawnTransform(SpawnRotation, SpawnLocation);

		Arrow = GetWorld()->SpawnActorDeferred<AArrow>(ArrowClass, SpawnTransform);
		if (Arrow)
		{
			Arrow->SetArrowSpeed(ArrowSpeedVal);
			UGameplayStatics::FinishSpawningActor(Arrow, SpawnTransform);
			UGameplayStatics::PlaySoundAtLocation(this, ShootSound, GetActorLocation());
		}
	}
}
