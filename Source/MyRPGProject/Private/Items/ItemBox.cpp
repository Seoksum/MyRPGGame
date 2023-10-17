// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBox.h"
#include "Components/BoxComponent.h"
//#include "GameData/GameCollision.h"
#include "Interface/CharacterItemInterface.h"
#include "Engine/AssetManager.h"
#include "Items/ItemDataAsset.h"



// Sets default values
AItemBox::AItemBox()
{
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	//CollisionComp->SetCollisionProfileName(COLLECTIBLE);
	CollisionComp->SetBoxExtent(FVector());
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AItemBox::OnBeginOverlap);
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(CollisionComp);
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponCount = 3;
	BoxIndex = 0;
}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();

	UAssetManager& Manager = UAssetManager::Get();
	TArray<FPrimaryAssetId> Assets;
	Manager.GetPrimaryAssetIdList(TEXT("ItemDataAsset"), Assets);
	if (Assets.Num() > 0)
	{
		if (BoxIndex == 0)
		{
			BoxIndex = FMath::RandRange(0, Assets.Num() - 1 - WeaponCount);
		}
		FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets[BoxIndex]));
		if (AssetPtr.IsPending())
		{
			AssetPtr.LoadSynchronous();
		}
		Item = Cast<UItemDataAsset>(AssetPtr.Get());
		MeshComp->SetStaticMesh(Item->GetLazyLoadedMesh());
	}
}

void AItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}

void AItemBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Item == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Item is null"));
		return;
	}

	ICharacterItemInterface* Player = Cast<ICharacterItemInterface>(OtherActor);
	if (Player)
	{
		Player->TakeItem(this);
	}

}

void AItemBox::OnPickedUp()
{
	Destroy();

	//MeshComp->SetVisibility(false);
	//MeshComp->SetSimulatePhysics(false);
	//MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

