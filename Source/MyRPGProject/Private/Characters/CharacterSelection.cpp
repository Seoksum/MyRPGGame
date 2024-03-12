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
	GreystoneSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("GreystoneScene"));
	GreystoneSceneComp->SetupAttachment(RootComponent);
	for (int32 i = 1; i <= 3; i++)
	{
		class USkeletalMeshComponent* GreystoneSkeletalMesh;
		FString FormattedNum = FString::Printf(TEXT("Greystone%d"), i);
		GreystoneSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>((TEXT("%s"), *FormattedNum), false);
		GreystoneSkeletalMesh->SetupAttachment(GreystoneSceneComp);
		GreyStoneArray.Add(GreystoneSkeletalMesh);
	}

	// Countess
	CountessSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("CountessScene"));
	CountessSceneComp->SetupAttachment(RootComponent);

	for (int32 i = 1; i <= 3; i++)
	{
		class USkeletalMeshComponent* CountessSkeletalMesh;
		FString FormattedNum = FString::Printf(TEXT("Countess%d"), i);
		CountessSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>((TEXT("%s"), *FormattedNum),false);
		CountessSkeletalMesh->SetupAttachment(CountessSceneComp);
		CountessArray.Add(CountessSkeletalMesh);
	}
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

void ACharacterSelection::SelectCharacter(ECharacterType InCharacterType)
{
	CharacterMeshIdx = 0;
	if (InCharacterType == ECharacterType::CHAR_GreyStone)
	{
		GreyStoneArray[CharacterMeshIdx]->SetVisibility(true);
		HideCountess();
	}
	else if (InCharacterType == ECharacterType::CHAR_Countess)
	{
		CountessArray[CharacterMeshIdx]->SetVisibility(true);
		HideGreystone();
	} 
}

void ACharacterSelection::NextOrBefore(ECharacterType InCharacterType, bool IsNext)
{
	TArray<USkeletalMeshComponent*> temp;
	if (InCharacterType == ECharacterType::CHAR_GreyStone) { temp = GreyStoneArray; }
	else if (InCharacterType == ECharacterType::CHAR_Countess) { temp = CountessArray; }

	temp[CharacterMeshIdx]->SetVisibility(false);
	
	if (IsNext) { CharacterMeshIdx = (CharacterMeshIdx + 1) % temp.Num(); }
	else { CharacterMeshIdx = (CharacterMeshIdx + (temp.Num() - 1)) % temp.Num(); }

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



