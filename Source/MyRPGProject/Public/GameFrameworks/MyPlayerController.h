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


	void ApplyHUDChanges();	//Hud state�� üũ�ϰ�,�츮�� ���ϴ� hud state�� ����(�ٲٱ�)�ϱ����� �Լ�
	uint8 GetHUDState(); // Hudstate �޾ƿ��� �Լ�


	virtual void ChangeHUD(uint8 NewState); // ���ο� hudstate�� �޾ƿ� �� applyHUDChanges ȣ��
	virtual void RemoveHUD(uint8 NewState);

	bool ApplyHUD(UUserWidget* WidgetToApply, bool bShowMouseCursor, bool EnableClickEvents); // screen�� hud�� ������ �� �������� ��ȯ


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
