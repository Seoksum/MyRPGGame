// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/HealthInterface.h"
#include "GameFramework/Actor.h"
#include "Characters/Character_Greystone.h"
#include "GameData/MyGameSingleton.h"
#include "GameFrameworks/MyGameInstance.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	bWantsInitializeComponent = true;

}

// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	MaxLevel = 4;
	CurrentLevel = 1;
}

void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	//SetLevelStat(CurrentLevel);
	//MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}


void UMyStatComponent::SetLevelStat(int32 NewLevel)
{
	CurrentLevel = FMath::Clamp<float>(NewLevel, 1, MaxLevel);
	MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BaseStat = MyGameInstance->GetCharacterStat(CurrentLevel);
	MaxHp = BaseStat.MaxHp;
	MaxMana = BaseStat.MaxMana;
	SetHp(MaxHp);
	SetMana(MaxHp);

	//CurrentLevel = FMath::Clamp<float>(NewLevel, 1, UMyGameSingleton::Get().MaxLevel);
	//BaseStat = UMyGameSingleton::Get().GetCharacterStat(CurrentLevel-1);
	//SetHp(GetTotalStat().MaxHp); 
	//SetMana(GetTotalStat().MaxMana);
	
	OnStatChanged.Broadcast(GetTotalStat());
}


void UMyStatComponent::SetHp(float Hp)
{
	CurrentHp = FMath::Clamp<float>(Hp, 0.f, BaseStat.MaxHp);
	if (CurrentHp <= 0)
	{
		CurrentHp = 0;
		if (GetOwner()->Implements<UHealthInterface>())
		{
			IHealthInterface::Execute_OnDeath(GetOwner());
		}
	}
	OnHpChanged.Broadcast(CurrentHp);

}

void UMyStatComponent::SetMana(float Mana)
{
	CurrentMana = FMath::Clamp(Mana, 0.f, BaseStat.MaxMana);
	OnManaChanged.Broadcast(CurrentMana,GetMaxMana());
}

void UMyStatComponent::SetExp(int32 Exp)
{
	CurrentExp += Exp;
	float LevelExp = BaseStat.Exp;
	if (LevelExp <= CurrentExp)
	{
		CurrentLevel = FMath::Clamp<int32>(CurrentLevel + 1, 1, MaxLevel);
		OnPlayerLevelUp.Broadcast(static_cast<int32>(CurrentLevel));
		CurrentExp -= LevelExp;
	}
}

void UMyStatComponent::OnAttacked(float DamageAmount)
{
	const float PrevHp = CurrentHp;
	SetHp(FMath::Clamp<float>(PrevHp - DamageAmount, 0.f, BaseStat.MaxHp));
}

void UMyStatComponent::OnAttacking(float ManaAmount)
{
	const float PrevMana = CurrentMana;
	SetMana(FMath::Clamp(PrevMana - ManaAmount, 0.f, BaseStat.MaxMana));
}

void UMyStatComponent::UseHpPotion(float Amount)
{
	SetHp(CurrentHp + Amount);
}

void UMyStatComponent::UseManaPotion(float Amount)
{
	SetMana(CurrentMana + Amount);
}

void UMyStatComponent::SetWeaponStat(const FCharacterStat& NewWeaponStat)
{
	WeaponStat = NewWeaponStat;
	OnAddWeaponAttack.Broadcast(WeaponStat.Attack);
}

