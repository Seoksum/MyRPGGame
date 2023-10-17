// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HealthInterface.h"
#include "Enemy.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemyDeath, int32);
DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBossJump, TSubclassOf<class UCameraShakeBase>);

UCLASS()
class MYRPGPROJECT_API AEnemy : public ACharacter, public IHealthInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void OnDeath_Implementation();

	void EnemyDeath();

	virtual void Attack();


	
protected:

	UPROPERTY(VisibleAnywhere, Category = "AnimInstance")
	class UEnemy_AnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere,Category="UI")
	class UWidgetComponent* HpBar;

	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 Level;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float EnemyExp;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item")
	TSubclassOf<class AItemBox> ItemBoxClass;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	class AItemBox* ItemBox;

	FTimerHandle DeathTimerHandle;

public:

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	class UMyStatComponent* Stat;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool IsDeath = false;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool IsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* DeathSound;

	FOnEnemyDeath OnEnemyDeath;

	FOnAttackEnd OnAttackEnd;

	FOnBossJump OnBossJump;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	int32 EnemyIndex;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	int32 ItemBoxIndex;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	class USkeletalMeshComponent* Weapon;


};
