// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Character_Parent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "Kismet/KismetSystemLibrary.h"
//#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFrameworks/MyGameModeBase.h"
#include "Components/MyStatComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/HPWidget.h"
#include "UI/InGame.h"
#include "Components/TextBlock.h"
#include "ClimbingWall.h"
#include "Physics/ABCollision.h"
#include "Enemies/Enemy.h"
#include "Items/ItemBox.h"
#include "Items/WeaponItemDataAsset.h"
#include "Items/WeaponItemDataAsset_Gun.h"
#include "Items/WeaponItemDataAsset_Bow.h"
#include "Items/WeaponItemDataAsset_Sword.h"
#include "Interface/MyGameModeInterface.h"
#include "Interface/ChangeHUDInterface.h"
#include "Interface/MyGameInstanceInterface.h"
#include "GameData/CharacterEnum.h"


// Sets default values
ACharacter_Parent::ACharacter_Parent()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->JumpZVelocity = 500.f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 600.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	GetCapsuleComponent()->BodyInstance.SetCollisionProfileName(FName("PlayerCharacter"));
	//GetCapsuleComponent()->SetCollisionProfileName(FName("MyCharacter"));
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	


	Stat = CreateDefaultSubobject<UMyStatComponent>(TEXT("STAT"));
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 220.f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));
	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 50.f));
	}

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	CurrentWeaponIndex = EWeapon::None;

	bIsSprinting = false;
	IsDeath = false;
	ZoomedFOV = 65.f;
	ZoomInterpSpeed = 20.f;

	Level = 1;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	bOnInventoryHUDMode = false;
}

// Called when the game starts or when spawned
void ACharacter_Parent::BeginPlay()
{
	Super::BeginPlay();

	DefaultFOV = Camera->FieldOfView;
	
}

void ACharacter_Parent::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->SetLevelStat(Level);

	HpBar->InitWidget();
	UHPWidget* HpWidget = Cast<UHPWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(Stat);
		HpWidget->BindMana(Stat);
	}

	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, Enemies);
	for (AActor* actor : Enemies)
	{
		AEnemy* Enemy = Cast<AEnemy>(actor);
		Enemy->OnBossJump.AddUObject(this, &ACharacter_Parent::CameraShake);
		Enemy->OnEnemyDeath.AddUObject(this, &ACharacter_Parent::IncreaseExp);
	}

	Stat->OnPlayerLevelUp.AddUObject(this, &ACharacter_Parent::LevelUp);

}

// Called every frame
void ACharacter_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (CurrentWeaponIndex == EWeapon::Gun || CurrentWeaponIndex == EWeapon::Bow)
	//{
	//	float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;
	//	float NewFOV = FMath::FInterpTo(Camera->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);
	//	Camera->SetFieldOfView(NewFOV);
	//}

	if (bIsClimbingUp && bIsOnWall)
	{
		FVector Loc = GetActorLocation();
		SetActorLocation(FVector(Loc.X, Loc.Y, Loc.Z + 1.5f));
	}
}

// Called to bind functionality to input
void ACharacter_Parent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter_Parent::DoubleJump);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ACharacter_Parent::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ACharacter_Parent::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACharacter_Parent::Yaw);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACharacter_Parent::Pitch);
	PlayerInputComponent->BindAxis(TEXT("CameraZoom"), this, &ACharacter_Parent::CameraZoom);



	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &ACharacter_Parent::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &ACharacter_Parent::StopSprinting);

	PlayerInputComponent->BindAction(TEXT("Zoom"), EInputEvent::IE_Pressed, this, &ACharacter_Parent::BeginZoom);
	PlayerInputComponent->BindAction(TEXT("Zoom"), EInputEvent::IE_Released, this, &ACharacter_Parent::EndZoom);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacter_Parent::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACharacter_Parent::EndCrouch);

	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &ACharacter_Parent::Interact);

	PlayerInputComponent->BindAction(TEXT("Inventory"), EInputEvent::IE_Pressed, this, &ACharacter_Parent::SelectInventory);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ACharacter_Parent::Attack);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Released, this, &ACharacter_Parent::StopFire);

	PlayerInputComponent->BindAction(TEXT("ClimbingUp"), EInputEvent::IE_Pressed, this, &ACharacter_Parent::PressClimbingUp);

}

void ACharacter_Parent::OnDeath_Implementation()
{
	if (IsDeath)
		return;

	IsDeath = true;
	
	IMyGameModeInterface* MyGameMode = Cast<IMyGameModeInterface>(GetWorld()->GetAuthGameMode());
	if (MyGameMode)
	{
		MyGameMode->PawnKilled(this);
	}
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	
	DisableInput(PlayerController);
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ACharacter_Parent::UpDown(float Value)
{
	if (Value == 0.f || bIsOnWall)
		return;

	AddMovementInput(GetActorForwardVector(), Value);
}

void ACharacter_Parent::LeftRight(float Value)
{
	if (Value == 0.f || bIsOnWall)
		return;

	AddMovementInput(GetActorRightVector(), Value);
}
void ACharacter_Parent::Yaw(float Value)
{
	AddControllerYawInput(Value);
}

void ACharacter_Parent::Pitch(float Value)
{
	AddControllerPitchInput(Value);
}

// ShiftŰ�� ���� ĳ������ �̵��ӵ��� ������Ű�� �Լ�
void ACharacter_Parent::Sprint()
{
	if (!bIsSprinting)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 1200.f;
	}
}
// ShiftŰ�� �� ĳ������ �̵��ӵ��� ó�� ������ �����ϴ� �Լ�
void ACharacter_Parent::StopSprinting()
{
	if (bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
}

void ACharacter_Parent::DoubleJump()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bIsOnWall = false;

	if (DoubleJumpCounter == 0)
	{
		ACharacter::LaunchCharacter(FVector(0.f, 0.f, 600.f), false, true);
		IsDoubleJumping = false;
		DoubleJumpCounter++;
	}

	else if (DoubleJumpCounter == 1)
	{
		ACharacter::LaunchCharacter(FVector(0.f, 0.f, 600.f), false, true);
		DoubleJumpCounter++;
		IsDoubleJumping = true;
	}
	else
		return;
}

void ACharacter_Parent::Landed(const FHitResult& Hit)
{
	DoubleJumpCounter = 0;
}

void ACharacter_Parent::CameraZoom(const float Value)
{
	if (Value == 0.f)
		return;

	const float NewTargetArmLength = SpringArm->TargetArmLength + Value * 10.f;
	SpringArm->TargetArmLength = FMath::Clamp(NewTargetArmLength, 200.f, 1000.f);
}

void ACharacter_Parent::BeginZoom()
{
	bWantsToZoom = true;
}

void ACharacter_Parent::EndZoom()
{
	bWantsToZoom = false;
}

void ACharacter_Parent::BeginCrouch()
{
	Crouch();
}

void ACharacter_Parent::EndCrouch()
{
	UnCrouch();
}

void ACharacter_Parent::AttackHitCheck() // �⺻ ����
{
	if (CurrentWeaponIndex == EWeapon::None || CurrentWeaponIndex == EWeapon::Sword)
	{
		TArray<FHitResult> TraceHits;
		FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), true, this);

		const float AttackRange = 40.f;

		const FVector TraceStart = GetActorLocation();
		const FVector TraceEnd = TraceStart + (GetActorForwardVector() * AttackRange); // 150.0f
		FCollisionShape SweepShape = FCollisionShape::MakeSphere(100.0f);

		bool bResult = GetWorld()->SweepMultiByChannel(TraceHits, TraceStart, TraceEnd, FQuat::Identity, CCHANNEL_ATTACK, SweepShape);
		if (bResult)
		{
			for (FHitResult& Hit : TraceHits)
			{
				AEnemy* Enemy = Cast<AEnemy>(Hit.Actor);
				if (Enemy && !Enemy->IsDeath)
				{
					FDamageEvent DamageEvent;
					Enemy->TakeDamage(Stat->GetTotalStat().Attack, DamageEvent, GetController(), this);
					//if (Particle)
					//{
					//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Enemy->GetTransform());
					//}
				}
			}
		}
	}
}

void ACharacter_Parent::Attack()
{
	if (IsAttacking)
		return;

	if (CurrentWeaponIndex == EWeapon::Sword)
	{
		if (SwordAsset) { SwordAsset->WeaponAttack(this); }
	}

	else if (CurrentWeaponIndex == EWeapon::Gun)
	{
		if (GunAsset)
		{
			GunAsset->WeaponAttack(this);
		}
	}
	else if (CurrentWeaponIndex == EWeapon::Bow)
	{
		if (BowAsset) { BowAsset->WeaponAttack(this); }
	}

	return;
}

void ACharacter_Parent::StopFire()
{
	if (CurrentWeaponIndex == EWeapon::Gun && GunAsset)
	{
		GunAsset->StopFire();
	}
}

void ACharacter_Parent::EndAttack_Q()
{
	FString Q_Str;
	if (Remaining_SkillQ < 1)
	{
		Q_Str = FString::Printf(TEXT("Q"));
		IsAttackingQ = false;
		GetWorldTimerManager().ClearTimer(QSkillHandle);
	}
	else
	{
		Q_Str = FString::Printf(TEXT("%01d "), Remaining_SkillQ);
	}

	InGameWidget->Text_Q->SetText(FText::FromString(Q_Str));
	--Remaining_SkillQ;
}

void ACharacter_Parent::EndAttack_E()
{
	FString E_Str;
	if (Remaining_SkillE < 1)
	{
		E_Str = FString::Printf(TEXT("E"));
		IsAttackingE = false;
		GetWorldTimerManager().ClearTimer(ESkillHandle);
	}
	else
	{
		E_Str = FString::Printf(TEXT("%01d "), Remaining_SkillE);
	}

	InGameWidget->Text_E->SetText(FText::FromString(E_Str));
	--Remaining_SkillE;
}

void ACharacter_Parent::EndAttack_R()
{
	FString R_Str;

	if (Remaining_SkillR < 1)
	{
		R_Str = FString::Printf(TEXT("R"));
		IsAttackingR = false;
		GetWorldTimerManager().ClearTimer(RSkillHandle);
	}

	else
	{
		R_Str = FString::Printf(TEXT("%01d "), Remaining_SkillR);
	}
	InGameWidget->Text_R->SetText(FText::FromString(R_Str));
	--Remaining_SkillR;
}



float ACharacter_Parent::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Stat->OnAttacked(DamageAmount);
	return DamageAmount;
}

// �κ��丮 ����

void ACharacter_Parent::Interact()
{
	if (CurrentInteractableItemAsset != nullptr)
	{
		//CurrentItemBox->OnPickedUp();
		CurrentItemBox->Destroy();
		AddItemAssetToInventory(CurrentInteractableItemAsset);
	}
}

bool ACharacter_Parent::AddItemAssetToInventory(class UItemDataAsset* Item)
{
	if (Item != NULL)
	{
		Inventory->AddItemData(Item);
		CurrentInteractableItemAsset = nullptr;
		return true;
	}
	return false;
}


void ACharacter_Parent::UseItemDataAsset(class UItemDataAsset* Item)
{
	Item->Use(this);

	if (Item->Type != EItemType::Weapon)
	{
		Inventory->RemoveItemData(Item); 
	}
}

void ACharacter_Parent::SwitchWeaponItemData(int32 Index, class UWeaponItemDataAsset* WeaponItem)
{
	if (WeaponItem)
	{
		if (WeaponItem->WeaponMesh.IsPending())
		{
			WeaponItem->WeaponMesh.LoadSynchronous();
		}
		Weapon->SetSkeletalMesh(WeaponItem->WeaponMesh.Get());
	}

	CurrentWeaponIndex = Index;
	SpringArm->TargetArmLength = 550.f;
	CurrentWeaponItemAsset = WeaponItem;
	Stat->SetWeaponStat(WeaponItem->WeaponStat);
	
	if (Index == EWeapon::Sword)
	{
		SwordAsset = Cast<UWeaponItemDataAsset_Sword>(CurrentWeaponItemAsset);
		SetupPlayerView(FVector(0.f, 0.f, 0.f), FVector(0.f, 0.f, 0.f));
	}
	else if (Index == EWeapon::Gun)
	{
		GunAsset = Cast<UWeaponItemDataAsset_Gun>(CurrentWeaponItemAsset);
		SetupPlayerView(FVector(0.f, 40.f, 70.f), FVector(0.f, 60.f, 0.f));
	}
	else if (Index == EWeapon::Bow)
	{
		BowAsset = Cast<UWeaponItemDataAsset_Bow>(CurrentWeaponItemAsset);
		SetupPlayerView(FVector(0.f, 40.f, 70.f), FVector(0.f, 60.f, 0.f));
	}

	//if (Index == EWeapon::Sword)
	//{
	//	SwordAsset = Cast<UWeaponItemDataAsset_Sword>(CurrentWeaponItemAsset);
	//	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SwordSocket"));
	//	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	//	SpringArm->SocketOffset = FVector(0.f, 0.f, 0.f);
	//}
	//else if (Index == EWeapon::Gun)
	//{
	//	GunAsset = Cast<UWeaponItemDataAsset_Gun>(CurrentWeaponItemAsset);
	//	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
	//	SpringArm->SetRelativeLocation(FVector(0.f, 40.f, 70.f));
	//	SpringArm->SocketOffset = FVector(0.f, 60.f, 0.f);
	//}
	//else if (Index == EWeapon::Bow)
	//{
	//	BowAsset = Cast<UWeaponItemDataAsset_Bow>(CurrentWeaponItemAsset);
	//	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("BowSocket"));
	//	SpringArm->SetRelativeLocation(FVector(0.f, 40.f, 70.f));
	//	SpringArm->SocketOffset = FVector(0.f, 60.f, 0.f);
	//}

	Camera->SetFieldOfView(DefaultFOV);
}

void ACharacter_Parent::SetupPlayerView(FVector Location, FVector SocketOffset)
{
	IMyGameInstanceInterface* GameInstance = Cast<IMyGameInstanceInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		TMap<int32, FName> WeaponArray = GameInstance->GetWeaponArray();
		if (WeaponArray.Num() > 0)
		{
			const FName WeaponSocketName = WeaponArray[CurrentWeaponIndex];
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);
			SpringArm->SetRelativeLocation(Location);
			SpringArm->SocketOffset = FVector(SocketOffset);
		}
	}
}

void ACharacter_Parent::SelectInventory()
{
	IChangeHUDInterface* PlayerController = Cast<IChangeHUDInterface>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		if (bOnInventoryHUDMode)
		{
			PlayerController->RemoveHUD(EHUDStates::HS_Inventory);
			bOnInventoryHUDMode = false;
		}
		else
		{
			PlayerController->ChangeHUD(EHUDStates::HS_Inventory);
			bOnInventoryHUDMode = true;
		}
	}

}

void ACharacter_Parent::PressClimbingUp()
{
	if (bIsClimbingUp)
		return;

	FVector Start = GetCapsuleComponent()->GetRelativeLocation();
	FVector End = GetCapsuleComponent()->GetRelativeLocation() + GetCapsuleComponent()->GetForwardVector() * 300.f;

	float CapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	float CapsuleHeight = CapsuleHalfHeight * 2.f;

	float diff = 150.f;
	Start.Z += CapsuleHeight + diff;
	End.Z += CapsuleHeight + diff;

	FHitResult OutHit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_GameTraceChannel6, QueryParams);

	if (bResult) // Climbing 
	{
		bIsOnWall = true;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		bIsClimbingUp = true;
	}

	else
	{
		if (bIsOnWall) // Climbing �Ϸ�
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			bIsOnWall = false;
			bIsClimbingComplete = true;
		}
		else { return; }
	}

	GetWorld()->GetTimerManager().SetTimer(ClimbingHandle, this, &ACharacter_Parent::ReleaseClimbingUp, 1.5f, true);
}

void ACharacter_Parent::ReleaseClimbingUp()
{
	bIsClimbingUp = false;
	GetWorld()->GetTimerManager().ClearTimer(ClimbingHandle);
	bIsClimbingComplete = false;
}

void ACharacter_Parent::CameraShakeCheck()
{
	if (AttackCamShake)
	{
		CameraShake(AttackCamShake);
	}
}

void ACharacter_Parent::CameraShake(TSubclassOf<class UCameraShakeBase> Cam)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->ClientPlayCameraShake(Cam);
	}
}

void ACharacter_Parent::LevelUp(int32 PlayerLevel)
{
	// ��ƼŬ,���� ����
	UGameplayStatics::SpawnEmitterAttached(LevelupEffect, GetMesh());
	UGameplayStatics::PlaySoundAtLocation(this, LevelupSound, GetActorLocation());

	// ������
	Level = PlayerLevel;
	Stat->SetLevelStat(Level); // ü��,���� MAX ������ ����
}

UMyStatComponent* ACharacter_Parent::GetMyStatComponent()
{
	if (Stat)
	{
		return Stat;
	}
	return NewObject<UMyStatComponent>();
}

UInventoryComponent* ACharacter_Parent::GetInventoryComponent()
{
	if (Inventory)
	{
		return Inventory;
	}
	return NewObject<UInventoryComponent>();
}

void ACharacter_Parent::TakeItem(class AItemBox* ItemBox)
{
	CurrentItemBox = ItemBox;
	UItemDataAsset* ItemData = CurrentItemBox->Item;

	CurrentInteractableItemAsset = ItemData;
	if (ItemData->Type == EItemType::Weapon)
	{
		UWeaponItemDataAsset* WeaponItemData = Cast<UWeaponItemDataAsset>(ItemData);
		CurrentWeaponItemAsset = WeaponItemData;
	}

	//switch (ItemData->Type)
	//{
	//case EItemType::Weapon:
	//	EquipWeapon(ItemData);
	//	break;
	//case EItemType::Potion:
	//	UsePotion(ItemData);
	//	break;
	//default:
	//	break;
	//}
}


void ACharacter_Parent::IncreaseExp(int32 Exp)
{
	Stat->SetExp(Exp);
}

void ACharacter_Parent::AddInGameWidget(class UInGame* InGame)
{
	InGameWidget = InGame;
	if (InGameWidget)
	{
		InGameWidget->BindStat(Stat);

		Stat->OnAddWeaponAttack.AddUObject(InGame, &UInGame::UpdateAttack);
		Stat->OnStatChanged.AddUObject(InGame, &UInGame::UpdatePlayerStat);
	}
}

// AnimInstance
bool ACharacter_Parent::GetIsDoubleJumping() { return IsDoubleJumping; }
int32 ACharacter_Parent::GetCurrentWeaponIndex() { return CurrentWeaponIndex; }
bool ACharacter_Parent::GetIsOnWall() { return bIsOnWall; }
bool ACharacter_Parent::GetIsClibmingUp() { return bIsClimbingUp; }
bool ACharacter_Parent::GetIsDeath() { return IsDeath; }