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


public:

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

	UPROPERTY(VisibleInstanceOnly, Category = "Stat")
	float MaxHp;

	UPROPERTY(VisibleInstanceOnly, Category = "Stat")
	float MaxMana;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat")
	float CurrentHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	float CurrentMana;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	float CurrentExp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	float CurrentLevel;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float MaxLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	FCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	FCharacterStat WeaponStat;

	UPROPERTY(VisibleInstanceOnly)
	class UMyGameInstance* MyGameInstance;


};
