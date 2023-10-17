// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Character_Parent.h"
#include "Character_Countess.generated.h"

/**
 *
 */



UCLASS()
class MYRPGPROJECT_API ACharacter_Countess : public ACharacter_Parent
{
	GENERATED_BODY()


public:

	ACharacter_Countess();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	virtual void AddInGameWidget(class UInGame* InGame) override;

	virtual void SetupPlayerView(FVector Location, FVector SocketOffset) override;

protected:

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	virtual void Attack() override;
	void AttackQ();
	void AttackE();
	void AttackR();


	UFUNCTION()
	void AttackCheck(int32 damage, float TraceDistance);

	virtual void PressClimbingUp() override;


private:

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);


private:

	UPROPERTY(VisibleAnywhere)
	class UAnimInstance_Countess* AnimInstance;

	UPROPERTY(VisibleAnywhere)
	int32 TotalAttackIndex;

	UPROPERTY()
	int32 AttackIndex = 0;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* LeftSword;




};
