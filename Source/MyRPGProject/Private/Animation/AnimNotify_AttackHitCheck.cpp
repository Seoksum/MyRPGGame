// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
#include "Interface/AttackHitCheckInterface.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		IAttackHitCheckInterface* Player = Cast<IAttackHitCheckInterface>(MeshComp->GetOwner());
		if (Player)
		{
			Player->AttackHitCheck();
			UE_LOG(LogTemp, Log, TEXT("Player Attack Hit"));
		}
	}
}

