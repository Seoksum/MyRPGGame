// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponItemDataAsset_Bow.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "TimerManager.h"
#include "Items/Arrow.h"
#include "Characters/Character_Parent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/SkeletalMeshSocket.h"

UWeaponItemDataAsset_Bow::UWeaponItemDataAsset_Bow()
{
	if (WeaponMesh.IsPending())
	{
		WeaponMesh.LoadSynchronous();
	}
	
	WeaponMeshComponent = WeaponMesh.Get();
	
	ArrowSpeedVal = 4000.f;
}

void UWeaponItemDataAsset_Bow::WeaponAttack(class ACharacter_Parent* InPlayer)
{
	Super::WeaponAttack(InPlayer);
	
	Player = InPlayer;
	Fire();
}

void UWeaponItemDataAsset_Bow::Fire()
{
	if (Player)
	{
		FActorSpawnParameters SpawnParams;
		FVector EyeLocation;
		FRotator EyeRotation;
		Player->GetActorEyesViewPoint(EyeLocation, EyeRotation); // OUT parameter
		FRotator SpawnRotation = EyeRotation;
		//FVector SpawnLocation = EyeLocation * 20.f;
		FVector SpawnLocation = WeaponMeshComponent->GetSocketLocation(FName("ArrowSocket"));
		FTransform SpawnTransform(SpawnRotation, EyeLocation);

		Arrow = Player->GetWorld()->SpawnActorDeferred<AArrow>(ArrowClass, SpawnTransform);
		if (Arrow)
		{
			Arrow->SetArrowSpeed(ArrowSpeedVal);
			UGameplayStatics::FinishSpawningActor(Arrow, SpawnTransform);
		}

		if (ShootSound)
		{
			UGameplayStatics::PlaySoundAtLocation(Player->GetWorld(), ShootSound, Player->GetActorLocation());
		}
	}
}
