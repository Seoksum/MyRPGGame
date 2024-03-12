// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalToMap.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

APortalToMap::APortalToMap()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PM(TEXT("StaticMesh'/Game/EnvironmentPack2/Meshes/SM_TargettingPortal.SM_TargettingPortal'"));
	if (PM.Succeeded())
	{
		MeshComp->SetStaticMesh(PM.Object);
	}
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	SphereComp->SetupAttachment(MeshComp);
	SphereComp->SetSphereRadius(100.f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APortalToMap::OnBeginOverlap);
	
}

void APortalToMap::OnBeginOverlap(UPrimitiveComponent* OverlappedcComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FLatentActionInfo LatentInfo;
	TArray<AActor*> PlayerStarts;
	FVector PlayerStartLocation;

	UGameplayStatics::LoadStreamLevel(GetWorld(), NextMapName, true, true, LatentInfo);
	const FName NextMap = *FString::Printf(TEXT("PS_%s"), *NextMapName.ToString());
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), NextMap, PlayerStarts);

	for (auto PlayerStart : PlayerStarts)
	{
		PlayerStartLocation = PlayerStart->GetActorLocation();
		OtherActor->SetActorLocation(PlayerStartLocation);
	}

	return;
}



