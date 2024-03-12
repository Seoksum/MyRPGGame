// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Characters/Character_Parent.h"
#include "Components/BoxComponent.h"
#include "GameData/GameCollision.h"

AItem::AItem()
{
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionComp->SetCollisionProfileName(COLLECTIBLE);
	CollisionComp->SetBoxExtent(FVector());
	RootComponent = CollisionComp;

}

void AItem::BeginPlay()
{
	Super::BeginPlay();

}

void AItem::Use(class ACharacter_Parent* PlayerCharacter)
{
}



