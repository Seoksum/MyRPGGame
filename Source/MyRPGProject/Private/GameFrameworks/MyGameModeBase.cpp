// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameworks/MyGameModeBase.h"
#include "Characters/Character_Parent.h"
#include "Characters/Character_Greystone.h"
#include "Characters/Character_Countess.h"
#include "GameFrameworks/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFrameworks/MyPlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "AI/AIController_Enemy.h"
#include "GameData/CharacterEnum.h"


AMyGameModeBase::AMyGameModeBase()
{
	// Player Controller
	PlayerControllerClass = AMyPlayerController::StaticClass();

	// Default Pawn 
	UWorld* World = GetWorld();
	if (World)
	{
		GameInstanceRef = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(World));
		if (GameInstanceRef)
		{
			CharTypeIndex = GameInstanceRef->GetCharacterTypeIndex();
			CharMeshIndex = GameInstanceRef->GetCharacterMeshIndex();

			if (CharTypeIndex == ECharacterIndex::Greystone)
			{
				static ConstructorHelpers::FClassFinder<ACharacter_Greystone> BP_Greystone1(TEXT("Blueprint'/Game/Blueprints/MainCharacter/Greystone/BP_Greystone.BP_Greystone_C'"));
				static ConstructorHelpers::FClassFinder<ACharacter_Greystone> BP_Greystone2(TEXT("Blueprint'/Game/Blueprints/MainCharacter/Greystone/BP_Greystone2.BP_Greystone2_C'"));
				static ConstructorHelpers::FClassFinder<ACharacter_Greystone> BP_Greystone3(TEXT("Blueprint'/Game/Blueprints/MainCharacter/Greystone/BP_Greystone3.BP_Greystone3_C'"));

				if (BP_Greystone1.Succeeded() && CharMeshIndex == 0)
					DefaultPawnClass = BP_Greystone1.Class;

				else if (BP_Greystone2.Succeeded() && CharMeshIndex == 1)
					DefaultPawnClass = BP_Greystone2.Class; //BP_Greystone1.Class;

				else if (BP_Greystone3.Succeeded() && CharMeshIndex == 2)
					DefaultPawnClass = BP_Greystone3.Class; //BP_Greystone1.Class;
			}

			else if (CharTypeIndex == ECharacterIndex::Countess)
			{
				static ConstructorHelpers::FClassFinder<ACharacter_Countess> BP_Countess1(TEXT("Blueprint'/Game/Blueprints/MainCharacter/Countess/BP_Countess.BP_Countess_C'"));
				static ConstructorHelpers::FClassFinder<ACharacter_Countess> BP_Countess2(TEXT("Blueprint'/Game/Blueprints/MainCharacter/Countess/BP_Countess2.BP_Countess2_C'"));
				static ConstructorHelpers::FClassFinder<ACharacter_Countess> BP_Countess3(TEXT("Blueprint'/Game/Blueprints/MainCharacter/Countess/BP_Countess3.BP_Countess3_C'"));

				if (BP_Countess1.Succeeded() && CharMeshIndex == 0)
					DefaultPawnClass = BP_Countess1.Class;

				else if (BP_Countess2.Succeeded() && CharMeshIndex == 1)
					DefaultPawnClass = BP_Countess2.Class;

				else if (BP_Countess3.Succeeded() && CharMeshIndex == 2)
					DefaultPawnClass = BP_Countess3.Class;

			}
		}
	}

	bUseSeamlessTravel = true;
	
}

void AMyGameModeBase::PawnKilled(class APawn* PawnKilled)
{
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{
		EndGame(false); // Player가 졌을 경우
	}

	for (AAIController_Enemy* Controller : TActorRange<AAIController_Enemy>(GetWorld()))
	{
		if (!Controller->IsBossAIDead())
		{
			return; // 현재 레벨에서 죽어있는 AI가 없다면 조기 return 
		}
	}

	EndGame(true); // 전부 확인 후 다 죽어있다면 Player 승리
}

void AMyGameModeBase::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}

//for (AController* Controller : TActorRange<AController>(GetWorld()))
//{
//	bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
//	Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
//}

// bIsWinner가 true인 경우
// AI 컨트롤러이고 && AI가 이겼을 때
// 플레이어 컨트롤러이고 && 플레이어가 이겼을 때