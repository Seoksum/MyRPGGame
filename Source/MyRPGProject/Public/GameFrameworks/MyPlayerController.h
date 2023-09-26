// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/ChangeHUDInterface.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGPROJECT_API AMyPlayerController : public APlayerController, public IChangeHUDInterface
{
	GENERATED_BODY()
	

public:
	AMyPlayerController();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

	virtual void RestartLevel() override;

	enum EHUDState : uint8
	{
		HS_Ingame,
		HS_Inventory,
		HS_Restart,
		HS_Win,
	};


	void ApplyHUDChanges();	//Hud state를 체크하고,우리가 원하는 hud state로 적용(바꾸기)하기위한 함수
	uint8 GetHUDState(); // Hudstate 받아오는 함수


	virtual void ChangeHUD(uint8 NewState); // 새로운 hudstate를 받아온 후 applyHUDChanges 호출
	virtual void RemoveHUD(uint8 NewState);

	bool ApplyHUD(UUserWidget* WidgetToApply, bool bShowMouseCursor, bool EnableClickEvents); // screen에 hud를 적용한 후 성공여부 반환


	void AddCrossWidget();
	void RemoveCrossWidget();

	


public:

	uint8 HUDState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UInGame> IngameHUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	class UInGame* InGameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> InventoryHUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	UUserWidget* InventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> RestartHUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	UUserWidget* RestartWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> CrosshairHUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	UUserWidget* CrosshairWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> WinnerHUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	UUserWidget* WinnerWidget;

	

	

private:

	UPROPERTY(VisibleAnywhere, Category = "Game")
	class UMyGameInstance* MyGameInstanceRef;

	UPROPERTY(VisibleAnywhere, Category = "Game")
	class UMySaveGame* MySaveGame;



};
