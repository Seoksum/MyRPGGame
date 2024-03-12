// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Character_Greystone.h"
#include "UI/InGame.h"
#include "Components/MyStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameData/GameCollision.h"
#include "GameData/CharacterEnum.h"


ACharacter_Greystone::ACharacter_Greystone()
{

}

void ACharacter_Greystone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// R 스킬 공격 중
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



void ACharacter_Greystone::Attack()
{
	Super::Attack();

	if (IsAttacking)
		return;

	IsAttacking = true;

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