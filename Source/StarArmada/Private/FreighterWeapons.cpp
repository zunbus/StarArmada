// © Hubert Filas 2026. All Rights Reserved.


#include "FreighterWeapons.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "F2FCannonBullet.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "F2FCannonBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AF2FCannonBullet* BulletActor = GetWorld()->SpawnActor<AF2FCannonBullet>(
			Bullet,
			Mesh->GetSocketLocation("BarrelSpawn"),
			Mesh->GetSocketRotation("BarrelSpawn"),
			Params
		);
		if (BulletActor && OwningFreighter){
			BulletActor->Outer=OwningFreighter;
		}
		


		AActor* Parent = GetAttachParentActor();
		FVector ParentVelocity = Parent ? Parent->GetVelocity() : FVector::ZeroVector;
		if (BulletActor){
			BulletActor->ProjectileMovement->Velocity += ParentVelocity;
		}
		

		
		if (FireSound){
			UGameplayStatics::PlaySoundAtLocation(
				this,
				FireSound,
				Mesh->GetSocketLocation("BarrelSpawn")
			);
		}
		

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

