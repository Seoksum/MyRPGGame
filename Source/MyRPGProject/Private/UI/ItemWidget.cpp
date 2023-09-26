// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Items/ItemDataAsset.h"
#include "Interface/CharacterItemInterface.h"


void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UseButton->OnClicked.AddDynamic(this, &UItemWidget::OnClickedUseButton);
	UseButton->ToolTipTextDelegate.BindUFunction(this, FName("GetToolTipUseButton"));
}

void UItemWidget::OnClickedUseButton()
{
	ICharacterItemInterface* Player = Cast<ICharacterItemInterface>(GetOwningPlayerPawn());
	if (Player)
	{
		Player->UseItemDataAsset(ItemData);
	}

}

FText UItemWidget::GetToolTipUseButton()
{
	return (("Click to {0} {1},{2}"), ItemData->UseActionText, ItemData->ItemName, ItemData->ItemDescription);
}


void UItemWidget::SetItemAssetInfo(class UItemDataAsset* PickItem)
{
	if (PickItem == nullptr)
		return;

	ItemData = PickItem;
	
	UTexture2D* ThumbnailImage = ItemData->Thumbnail;
	Thumbnail->SetBrushFromTexture(ThumbnailImage);
	
	FText Name = ItemData->ItemName;
	ItemName->SetText(Name);
}
