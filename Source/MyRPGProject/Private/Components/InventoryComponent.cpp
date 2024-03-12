// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Items/ItemDataAsset.h"

#include "Items/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	Capacity = 20.f;


}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}


void UInventoryComponent::AddItem(UItemDataAsset* Item)
{
	if (ItemArray.Num() >= Capacity || !Item)
		return;
	Item->OwingInventory = this;
	ItemArray.Add(Item);
	OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::RemoveItem(UItemDataAsset* Item)
{
	if (Item)
	{
		Item->OwingInventory = nullptr;
		ItemArray.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
	}
}


