// Fill out your copyright notice in the Description page of Project Settings.


#include "FreighterWeapons.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "F2FCannonBullet.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AFreighterWeapons::AFreighterWeapons()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	SetRootComponent(Mesh);
	AimMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aim Mesh"));
	AimMesh->SetupAttachment(Mesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SightshMeshAsset(
        TEXT("/Game/Graphics/Meshes/Sights/Sights.Sights")
    );

    if (SightshMeshAsset.Succeeded())
    {
        AimMesh->SetStaticMesh(SightshMeshAsset.Object);
    }

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFreighterWeapons::BeginPlay()
{
	Super::BeginPlay();
	AimMesh->AttachToComponent(
		Mesh,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		TEXT("BarrelSpawn")
	);
}


void AFreighterWeapons::Fire(){
	if (!locked){
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AF2FCannonBullet>(
			Bullet,
			AimMesh->GetComponentLocation(),
			Mesh->GetSocketRotation("BarrelSpawn"),
			Params
		);

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FireParticles, Mesh->GetSocketLocation("BarrelSpawn"),Mesh->GetSocketRotation("BarrelSpawn"));

		APlayerController* PC = GetWorld()->GetFirstPlayerController();

		if (PC)
		{
			PC->PlayerCameraManager->StartCameraShake(CameraShakeClass);
		}

		locked = true;
		FTimerHandle CooldownTimer;
		GetWorld()->GetTimerManager().SetTimer(
			CooldownTimer,
			this,
			&AFreighterWeapons::Release,
			CoolDown,
			false
		);
	}
	
	
}

void AFreighterWeapons::Release(){
	locked = false;
}

// Called every frame
void AFreighterWeapons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Active){
		AimMesh->SetVisibility(true);
	}
	else {
		AimMesh->SetVisibility(false);
	}

}

