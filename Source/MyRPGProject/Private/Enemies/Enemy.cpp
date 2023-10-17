// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/MyStatComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFrameworks/MyGameModeBase.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "UI/EnemyHPWidget.h"
#include "Characters/Character_Parent.h"
#include "Items/ItemBox.h"
#include "AI/AIController_Enemy.h"
#include "UI/EnemyHPWidget.h"
#include "Interface/MyGameModeInterface.h"
#include "Enemies/Enemy_AnimInstance.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	GetCapsuleComponent()->BodyInstance.SetCollisionProfileName(FName("Enemy"));
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	// AI Controller »ý¼º
	AIControllerClass = AAIController_Enemy::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Stat = CreateDefaultSubobject<UMyStatComponent>(TEXT("STAT"));

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 240.f));
	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarUserWidget(TEXT("WidgetBlueprint'/Game/UI/WBP_EnemyHpBar.WBP_EnemyHpBar_C'"));
	if (HpBarUserWidget.Succeeded())
	{
		HpBar->SetWidgetClass(HpBarUserWidget.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 50.f));
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	IsAttacking = false;
	IsDeath = false;
	ItemBoxIndex = 0;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UEnemy_AnimInstance>(GetMesh()->GetAnimInstance());

}

void AEnemy::Attack()
{
	if (IsAttacking || Stat->GetCurrentHp() <= 0.f)
		return;
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->OnAttacked(DamageAmount);

	return DamageAmount;
}

void AEnemy::OnDeath_Implementation()
{
	if (IsDeath)
		return;

	IsDeath = true;
	IMyGameModeInterface* MyGameMode = Cast<IMyGameModeInterface>(GetWorld()->GetAuthGameMode());
	if (MyGameMode)
	{
		MyGameMode->PawnKilled(this);
	}
	
	OnEnemyDeath.Broadcast(EnemyExp);
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AEnemy::EnemyDeath, 2.f, false);
}


void AEnemy::EnemyDeath()
{
	FTransform SpawnTransform(FRotator(0.f, 0.f, 0.f), GetActorLocation());

	ItemBox = GetWorld()->SpawnActorDeferred<AItemBox>(ItemBoxClass, SpawnTransform);
	if (ItemBox)
	{
		ItemBox->BoxIndex = ItemBoxIndex;
		UGameplayStatics::FinishSpawningActor(ItemBox, SpawnTransform);
	}
	GetWorldTimerManager().ClearTimer(DeathTimerHandle);
}


