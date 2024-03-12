// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item_Potion.h"
#include "Characters/Character_Parent.h"
#include "Components/MyStatComponent.h"
#include "Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Image.h"
#include "Characters/Character_Parent.h"

AItem_Potion::AItem_Potion()
{
	//MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	//MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//MeshComp->SetupAttachment(RootComponent);


	HpPotionVal = 15.f;
	ManaPotionVal = 15.f;
}

void AItem_Potion::BeginPlay()
{
	Super::BeginPlay();

}

void AItem_Potion::Use(ACharacter_Parent* PlayerCharacter)
{
	if (!PlayerCharacter)
		return;

	UMyStatComponent* Stat = PlayerCharacter->GetMyStatComponent();
	if (Stat)
	{
		if(PotionType == EPotionType::POTION_HP)
		{
			Stat->UseHpPotion(0); 
		}
		else if (PotionType == EPotionType::POTION_MANA)
		{
			Stat->UseManaPotion(0);
		}
	}
}

