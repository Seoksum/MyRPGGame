// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/CharacterStat.h"
#include "MyStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChanged,float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnManaChanged, float, float);
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerLevelUp, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStatChanged, const FCharacterStat&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddWeaponAttack, float);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYRPGPROJECT_API UMyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMyStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;


public:

	void SetLevelStat(int32 NewLevel);

	void SetHp(float Hp);
	
	void SetMana(float Mana);
	
	void SetExp(int32 Exp);

	void OnAttacked(float DamageAmount);
	void OnAttacking(float ManaAmount);

	void UseHpPotion(float Amount);
	void UseManaPotion(float Amount);

	void SetTotalStat(const FCharacterStat& TotalStat);


public:

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
		class UMyGameInstance* MyGameInstance;

	FOnHpChanged OnHpChanged;

	FOnManaChanged OnManaChanged;

	FOnDeath OnDeath;

	FOnPlayerLevelUp OnPlayerLevelUp;

	FOnStatChanged OnStatChanged;

	FOnAddWeaponAttack OnAddWeaponAttack;


public:

	FORCEINLINE float GetMaxHp() const { return BaseStat.MaxHp; }
	FORCEINLINE float GetMaxMana() const { return BaseStat.MaxMana; }
	FORCEINLINE float GetHpRatio() const { return (CurrentHp / BaseStat.MaxHp); }


	FORCEINLINE float GetCurrentLevel() const { return CurrentLevel; }
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE float GetCurrentMana() const { return CurrentMana; }

	void SetWeaponStat(const FCharacterStat& NewWeaponStat);

	FORCEINLINE FCharacterStat GetTotalStat() const { return BaseStat + WeaponStat; }




protected:

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	float MaxHp;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	float MaxMana;

	UPROPERTY(Transient, VisibleAnywhere, Category = "Stat")
	float CurrentHp;

	UPROPERTY(Transient, VisibleAnywhere, Category = "Stat")
	float CurrentMana;

	UPROPERTY(Transient, VisibleAnywhere, Category = "Stat")
	float CurrentExp;

	UPROPERTY(Transient, VisibleAnywhere, Category = "Stat")
	float CurrentLevel;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	FCharacterStat BaseStat;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	FCharacterStat WeaponStat;



};
