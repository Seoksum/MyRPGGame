// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon.h"
#include "Characters/Character_Parent.h"
#include "GameData/CharacterEnum.h"

// Sets default values
AWeapon::AWeapon()
{
	//SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	
	
}

void AWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Use(ACharacter_Parent* PlayerCharacter)
{
	Super::Use(PlayerCharacter);

	if (!PlayerCharacter)
		return;

	
}


void AWeapon::Attack()
{
}

void AWeapon::Attack(int32 damage, float TraceDistance, UParticleSystem* Particle)
{
}

