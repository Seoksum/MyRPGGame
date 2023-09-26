// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	//UItemWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized();

	UFUNCTION()
	void OnClickedUseButton();

	UFUNCTION()
	FText GetToolTipUseButton();

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* UseButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* Thumbnail;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemName;


// Item Data Asset 
public:

	UPROPERTY(BlueprintReadWrite, Category = "Item", meta = (ExposeOnSpawn = true))
	class UItemDataAsset* ItemData;

	void SetItemAssetInfo(class UItemDataAsset* PickItem);




};
