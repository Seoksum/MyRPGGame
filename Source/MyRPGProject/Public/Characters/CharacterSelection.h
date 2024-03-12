// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameData/CharacterEnum.h"
#include "CharacterSelection.generated.h"

UCLASS()
class MYRPGPROJECT_API ACharacterSelection : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACharacterSelection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	void SelectCharacter(ECharacterType InCharacterType);

	void NextOrBefore(ECharacterType InCharacterType, bool IsNext);

	void HideGreystone();
	void HideCountess();

	UPROPERTY(VisibleAnywhere)
	int32 CharacterMeshIdx = 0;

	//Scene Component
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* GreystoneSceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CountessSceneComp;

	UPROPERTY(VisibleAnywhere)
	TArray<USkeletalMeshComponent*> GreyStoneArray;

	UPROPERTY(VisibleAnywhere)
	TArray<USkeletalMeshComponent*> CountessArray;

};
