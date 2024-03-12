// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HealthInterface.h"
#include "Interface/CharacterItemInterface.h"
#include "Interface/InGameWidgetInterface.h"
#include "Interface/PlayerStateInterface.h"
#include "GameData/CharacterEnum.h"
#include "Character_Parent.generated.h"



UCLASS()
class MYRPGPROJECT_API ACharacter_Parent : public ACharacter, public IHealthInterface, public ICharacterItemInterface, public IInGameWidgetInterface, public IPlayerStateInterface
{
	GENERATED_BODY()

public:

	ACharacter_Parent();

protected:

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);
	void Pitch(float Value);

	void Sprint();
	void StopSprinting();

	void CameraZoom(const float Value);
	void BeginZoom();
	void EndZoom();

	void BeginCrouch();
	void EndCrouch();

	UFUNCTION()
	void DoubleJump();

	virtual void Landed(const FHitResult& Hit) override;

	virtual void Attack();
	void StopFire();

	UFUNCTION()
	void AttackHitCheck(float damage, float TraceDistance, class UParticleSystem* Particle);

	void AttackQ();
	void AttackE();
	void AttackR();

	void EndAttack_Q();
	void EndAttack_E();
	void EndAttack_R();

	virtual void OnDeath_Implementation() override;

	void IncreaseExp(int32 Exp);


public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Interact();

	void SelectInventory(); // 인벤토리 UI창 보기 

	virtual void CameraShakeCheck(); 
	void CameraShake(TSubclassOf<class UCameraShakeBase> Cam);

	void LevelUp(int32 PlayerLevel);



public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", Meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", Meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemy> EnemyClass;



	// Player State(AnimInstance)
public:

	UPROPERTY(VisibleAnywhere)
	class UBaseCharacterAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool bIsSprinting;

	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 DoubleJumpCounter;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool OnClickJumpButton;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool IsDoubleJumping;

	UPROPERTY(EditDefaultsOnly, Category ="State")
	int32 CurrentWeaponIndex;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool IsDeath;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	bool AttackMoving;


//Player State Interface 
public:

	virtual class UMyStatComponent* GetMyStatComponent() override;
	virtual class UInventoryComponent* GetInventoryComponent() override;

	virtual bool GetIsDoubleJumping() override;
	virtual bool GetIsJumping() override;
	virtual bool GetIsCrouch() override;
	virtual int32 GetCurrentWeaponIndex() override;
	virtual bool GetIsOnWall() override;
	virtual bool GetIsClibmingUp() override;
	virtual bool GetIsDeath() override;


protected:

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool IsAttacking = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool IsAttackingQ = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool IsAttackingE = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool IsAttackingR = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	int32 Remaining_SkillQ;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	int32 Remaining_SkillE;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	int32 Remaining_SkillR;

	FTimerHandle QSkillHandle;
	FTimerHandle ESkillHandle;
	FTimerHandle RSkillHandle;

	UPROPERTY(EditAnywhere, Category = "Attack")
	int32 MaxAttackIndex;

	UPROPERTY(EditAnywhere, Category = "Attack")
	int32 DefaultAttackIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Attack")
	int32 SwordAttackIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level;

	UPROPERTY()
	float Mana;


public:

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;

	UPROPERTY(VisibleAnywhere,Category="Stat")
	class UMyStatComponent* Stat;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	class UInventoryComponent* Inventory;

	bool bWantsToZoom;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float ZoomedFOV;

	// 보간 속도를 0.1 ~ 100 사이 값
	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.1f, ClampMax = 100.f))
	float ZoomInterpSpeed;

	float DefaultFOV;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TSubclassOf<UCameraShakeBase> AttackCamShake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystem* LevelupEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* LevelupSound;

	
	
	//Item 
protected:

	virtual void TakeItem(class AItemBox* ItemBox) override;

	virtual void UseItem(class UItemDataAsset* Item) override;

	virtual void SetupPlayerView(FVector SpringArmLocation, FVector SocketOffset);

	UPROPERTY(VisibleAnywhere)
	class AItemBox* CurrentItemBox;

	UPROPERTY(VisibleAnywhere, Category="Item")
	class UItemDataAsset* CurrentInteractable;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	class AWeapon_Sword* Sword;

	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<class AWeapon_Sword> SwordClass;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	class AWeapon_Gun* Gun;

	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<class AWeapon_Gun> GunClass;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	class AWeapon_Bow* Bow;

	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<class AWeapon_Bow> BowClass;


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* WeaponSkeletalMeshComp;

	void SwitchWeapon(int32 InWeaponIndex, class UWeaponItemDataAsset* WeaponItem); // 무기 교체 UI


	//Climbing
protected:

	void PressClimbingUp(); // 1번 키를 눌러 캐릭터 벽 타기

	void ReleaseClimbing();

	UPROPERTY(VisibleAnywhere, Category = "Climbing")
	bool bIsClimbingUp = false;

	UPROPERTY(VisibleAnywhere, Category = "Climbing")
	bool bIsOnWall = false;

	UPROPERTY(VisibleAnywhere, Category = "Climbing")
	bool bIsClimbingComplete = false;

	FTimerHandle ClimbingTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Climbing")
	float diff;


	// HUD
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInGame* InGameWidget;

	virtual void AddInGameWidget(class UInGame* InGame);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bOnInventoryHUDMode;
	

 };
