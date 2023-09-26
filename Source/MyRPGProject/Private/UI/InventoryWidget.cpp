// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWidget.h"
#include "Components/InventoryComponent.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "UI/ItemWidget.h"
#include "Items/ItemDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/PlayerStateInterface.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	IPlayerStateInterface* Player = Cast<IPlayerStateInterface>(GetOwningPlayerPawn());
	if (Player)
	{
		Inventory = Player->GetInventoryComponent();
		if (Inventory)
		{
			Inventory->OnInventoryUpdated.AddDynamic(this, &UInventoryWidget::RefreshInventory);
		}
	}
}

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnClickedCloseButton);
}

void UInventoryWidget::RefreshInventory()
{
	InventoryBox->ClearChildren();
	TArray<class UItemDataAsset*> CurrentItemAssets = Inventory->GetItemDataArray();

	UItemWidget* ItemWidget;
	for (auto& Item : CurrentItemAssets)
	{
		if (Item)
		{
			ItemWidget = CreateWidget<UItemWidget>(GetOwningPlayer(), ItemHUDClass);
			if (ItemWidget)
			{
				InventoryBox->AddChildToWrapBox(ItemWidget);
				ItemWidget->SetItemAssetInfo(Item);
			}
		}
	}
}

void UInventoryWidget::InitializeInventory(class UInventoryComponent* InventoryComponent)
{
	InventoryBox->ClearChildren();
	TArray<class UItemDataAsset*> DefaultItems = InventoryComponent->GetDefaultItems();

	UItemWidget* ItemWidget;
	for (auto& Item : DefaultItems)
	{
		if (Item)
		{
			ItemWidget = CreateWidget<UItemWidget>(GetOwningPlayer(), ItemHUDClass);
			if (ItemWidget)
			{
				InventoryBox->AddChildToWrapBox(ItemWidget);
				ItemWidget->SetItemAssetInfo(Item);
			}
		}
	}
}

void UInventoryWidget::OnClickedCloseButton()
{
	RemoveFromParent();
	GetOwningPlayer()->SetShowMouseCursor(false);
}
