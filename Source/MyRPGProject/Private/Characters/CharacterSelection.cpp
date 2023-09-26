// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterSelection.h"
#include "Kismet/GameplayStatics.h"
#include "GameData/CharacterEnum.h"
#include "GameFrameworks/CharacterSelectController.h"



// Sets default values
ACharacterSelection::ACharacterSelection()
{

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = RootScene;

	// Greystone
	Greystones = CreateDefaultSubobject<USceneComponent>(TEXT("Greystones"));
	Greystones->SetupAttachment(RootComponent);

	Greystone1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GREYSTONE1"));
	Greystone2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GREYSTONE2"));
	Greystone3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GREYSTONE3"));
	Greystone1->SetupAttachment(Greystones);
	Greystone2->SetupAttachment(Greystones);
	Greystone3->SetupAttachment(Greystones);
	GreyStoneArray.Add(Greystone1);
	GreyStoneArray.Add(Greystone2);
	GreyStoneArray.Add(Greystone3);

	// Countess
	Countesses = CreateDefaultSubobject<USceneComponent>(TEXT("Countesses"));
	Countesses->SetupAttachment(RootComponent);
	Countess1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("COUNTESS1"));
	Countess2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("COUNTESS2"));
	Countess3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("COUNTESS3"));
	Countess1->SetupAttachment(Countesses);
	Countess2->SetupAttachment(Countesses);
	Countess3->SetupAttachment(Countesses);

	CountessArray.Add(Countess1);
	CountessArray.Add(Countess2);
	CountessArray.Add(Countess3);

}

// Called when the game starts or when spawned
void ACharacterSelection::BeginPlay()
{
	Super::BeginPlay();

	HideGreystone();
	HideCountess();

	GreyStoneArray[0]->SetVisibility(true);

	ACharacterSelectController* PlayerController =
		Cast<ACharacterSelectController>(GetWorld()->GetFirstPlayerController());

	if (PlayerController)
	{
		//PlayerController->CreateCharacterMenu();
	}
}

void ACharacterSelection::SelectCharacter(int32 Index)
{
	CharacterMeshIdx = 0;
	if (Index == ECharacterIndex::Greystone)
	{
		GreyStoneArray[CharacterMeshIdx]->SetVisibility(true);
		HideCountess();
	}
	else if (Index == ECharacterIndex::Countess)
	{
		CountessArray[CharacterMeshIdx]->SetVisibility(true);
		HideGreystone();
	}
}

void ACharacterSelection::NextOrBefore(int32 CharacterType, bool IsNext)
{
	TArray<USkeletalMeshComponent*> temp;

	if (CharacterType == ECharacterIndex::Greystone)
		temp = GreyStoneArray;
	
	else if (CharacterType == ECharacterIndex::Countess)
		temp = CountessArray;


	temp[CharacterMeshIdx]->SetVisibility(false);
	
	if (IsNext)
	{
		CharacterMeshIdx = (CharacterMeshIdx + 1) % temp.Num();
	}
	else
	{
		CharacterMeshIdx = (CharacterMeshIdx + (temp.Num() - 1)) % temp.Num();
	}

	temp[CharacterMeshIdx]->SetVisibility(true);
}



void ACharacterSelection::HideGreystone()
{
	for (auto Greystone : GreyStoneArray)
	{
		Greystone->SetVisibility(false);
	}
}

void ACharacterSelection::HideCountess()
{
	for (auto Countess : CountessArray)
	{
		Countess->SetVisibility(false);
	}
}

