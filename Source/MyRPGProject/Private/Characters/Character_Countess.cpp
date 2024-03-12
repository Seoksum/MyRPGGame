// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Character_Countess.h"
#include "UI/InGame.h"
#include "Components/MyStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameData/CharacterEnum.h"


ACharacter_Countess::ACharacter_Countess()
{
	LeftSword = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftSword"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PM(TEXT("SkeletalMesh'/Game/Weapon/Sword/Sword1/SK_Blade_HeroSword11.SK_Blade_HeroSword11'"));
	if (PM.Succeeded())
	{
		LeftSword->SetSkeletalMesh(PM.Object);
	}
	LeftSword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("WeaponSocket_L"));
	LeftSword->SetVisibility(false);

	Level = 1;
}

void ACharacter_Countess::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	GetMesh()->HideBoneByName(TEXT("weapon_l"), EPhysBodyOp::PBO_None);
}

void ACharacter_Countess::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ACharacter_Countess::Attack()
{
	Super::Attack();

	if (IsAttacking)
		return;
}

void ACharacter_Countess::AddInGameWidget(class UInGame* InGame)
{
	Super::AddInGameWidget(InGame);
	if (InGame)
	{
		InGame->SetCountess(Level);
	}
}

void ACharacter_Countess::SetupPlayerView(FVector Location, FVector SocketOffset)
{
	Super::SetupPlayerView(Location, SocketOffset);

	if (CurrentWeaponIndex == EWeaponType::WEAPON_SWORD)
	{
		//LeftSword->SetSkeletalMesh(WeaponSkeletalMeshComp->SkeletalMesh);
		//LeftSword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("WeaponSocket_L"));
		LeftSword->SetVisibility(true);
	}
	else
	{
		LeftSword->SetVisibility(false);
	}

}