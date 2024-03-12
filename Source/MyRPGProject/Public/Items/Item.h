// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameData/CharacterEnum.h"
#include "Item.generated.h"

UCLASS()
class MYRPGPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:
	AItem();

	virtual void BeginPlay() override;

	virtual void Use(class ACharacter_Parent* PlayerCharacter);
	// �����۸��� ��� ȿ���� �ٸ� ���̹Ƿ� �����Լ��� ���� 


public:

	UPROPERTY(EditAnywhere, Category = "Enemy")
	EItemType ItemType;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	//class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UBoxComponent* CollisionComp;


	UPROPERTY()
	TWeakObjectPtr<class UInventoryComponent> OwingInventory;

};
