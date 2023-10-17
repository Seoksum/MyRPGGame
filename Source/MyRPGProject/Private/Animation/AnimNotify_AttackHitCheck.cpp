// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
#include "Interface/AnimationAttackInterface.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		IAnimationAttackInterface* Player = Cast<IAnimationAttackInterface>(MeshComp->GetOwner());
		if (Player)
		{
			Player->AttackHitCheck();
		}
	}
}

