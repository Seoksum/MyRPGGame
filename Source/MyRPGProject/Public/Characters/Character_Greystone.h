// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character_Parent.h"
#include "Character_Greystone.generated.h"

/**
 *
 */



UCLASS()
class MYRPGPROJECT_API ACharacter_Greystone : public ACharacter_Parent
{
	GENERATED_BODY()

public:

	ACharacter_Greystone();

	virtual void Tick(float DeltaTime) override;

	virtual void AddInGameWidget(class UInGame* InGame) override;

protected:

	virtual void BeginPlay() override;

	virtual void Attack() override;

	virtual void CameraShakeCheck() override;


};
