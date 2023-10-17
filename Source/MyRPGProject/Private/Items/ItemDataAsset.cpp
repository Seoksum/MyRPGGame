// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemDataAsset.h"
#include "Engine/StreamableManager.h"


UStaticMesh* UItemDataAsset::GetLazyLoadedMesh()
{
    if (Mesh.IsPending())
    {
        FStreamableManager Streamable;
        const FSoftObjectPath& AssetRef = Mesh.ToStringReference();
        Mesh = Cast<UStaticMesh>(Streamable.LoadSynchronous(AssetRef));
    }
    
    return Mesh.Get();
}

void UItemDataAsset::Use(ACharacter_Parent* PlayerCharacter)
{
    
}
