// © 2026 Hubert Filas. All Rights Reserved.


#include "Freighter.h"
#include "FreighterMeshSet.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFreighter::AFreighter()
{
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	SetRootComponent(Collision);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetGenerateOverlapEvents(true);
	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	Collision->SetCollisionResponseToAllChannels(ECR_Overlap);

 	HullMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hull Mesh"));
	HullMesh->SetupAttachment(Collision);

	HangarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hangar Mesh"));
	HangarMesh->SetupAttachment(HullMesh);

	BowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bow Mesh"));
	BowMesh->SetupAttachment(HullMesh);

	CargoPortsideMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cargo Pod Portside"));
	CargoPortsideMesh->SetupAttachment(HullMesh);
	
	CargoStarboardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cargo Pod Starboard"));
	CargoStarboardMesh->SetupAttachment(HullMesh);

	ThrustersMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thrusters Mesh"));
	ThrustersMesh->SetupAttachment(HullMesh);
	
	CommStationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Comm Station Mesh"));
	CommStationMesh->SetupAttachment(HullMesh);

	PCD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PCD Mesh"));
	PCD->SetupAttachment(HullMesh);
	
	Reactor1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Reactor 1 Mesh"));
	Reactor1->SetupAttachment(HullMesh);

	Reactor2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Reactor 2 Mesh"));
	Reactor2->SetupAttachment(HullMesh);

	PCDCover = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PCD Cover Mesh"));
	PCDCover->SetupAttachment(HullMesh);
	
	Reactor1Cover = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Reactor 1 Cover Mesh"));
	Reactor1Cover->SetupAttachment(HullMesh);

	Reactor2Cover = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Reactor 2 Cover Mesh"));
	Reactor2Cover->SetupAttachment(HullMesh);
	
	
	HullMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HullMesh->SetGenerateOverlapEvents(false);

	HangarMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HangarMesh->SetGenerateOverlapEvents(false);

	BowMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BowMesh->SetGenerateOverlapEvents(false);

	CargoPortsideMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CargoPortsideMesh->SetGenerateOverlapEvents(false);

	CargoStarboardMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CargoStarboardMesh->SetGenerateOverlapEvents(false);

	ThrustersMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ThrustersMesh->SetGenerateOverlapEvents(false);

	CommStationMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CommStationMesh->SetGenerateOverlapEvents(false);

	PCD->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PCD->SetGenerateOverlapEvents(false);

	Reactor1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Reactor1->SetGenerateOverlapEvents(false);

	Reactor2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Reactor2->SetGenerateOverlapEvents(false);

	PCDCover->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PCDCover->SetGenerateOverlapEvents(false);

	Reactor1Cover->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Reactor1Cover->SetGenerateOverlapEvents(false);

	Reactor2Cover->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Reactor2Cover->SetGenerateOverlapEvents(false);

	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFreighter::BeginPlay()
{
	Super::BeginPlay();
	if (FreighterMeshSet){
		Collision->SetBoxExtent(FreighterMeshSet->CollisionBounds);
		HullMesh->SetRelativeLocation(FreighterMeshSet->Pivot);
		HullMesh->SetSkeletalMesh(FreighterMeshSet->Hull);

		switch (Hangar){
			case EHangarType::Innovative:
				if(FreighterMeshSet->Categories["Hangars"].Variants["Innovative"].StaticMesh){
					HangarMesh->SetStaticMesh(FreighterMeshSet->Categories["Hangars"].Variants["Innovative"].StaticMesh);
					HangarMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case EHangarType::Classic:
				if(FreighterMeshSet->Categories["Hangars"].Variants["Classic"].StaticMesh){
					HangarMesh->SetStaticMesh(FreighterMeshSet->Categories["Hangars"].Variants["Classic"].StaticMesh);
					HangarMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case EHangarType::SkyView:
				if(FreighterMeshSet->Categories["Hangars"].Variants["SkyView"].StaticMesh){
					HangarMesh->SetStaticMesh(FreighterMeshSet->Categories["Hangars"].Variants["SkyView"].StaticMesh);
					HangarMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
		}
		switch (Bow){
			case EBowType::Storage:
				if(FreighterMeshSet->Categories["Bows"].Variants["Storage"].StaticMesh){
					BowMesh->SetStaticMesh(FreighterMeshSet->Categories["Bows"].Variants["Storage"].StaticMesh);
					BowMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case EBowType::Terraformator:
				if(FreighterMeshSet->Categories["Bows"].Variants["Terraformator"].StaticMesh){
					BowMesh->SetStaticMesh(FreighterMeshSet->Categories["Bows"].Variants["Terraformator"].StaticMesh);
					BowMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
		}
		switch (CargoPodPortside){
			case ECargoPodType::Small:
				if (FreighterMeshSet->Categories["CargoPodsPortside"].Variants["Small"].StaticMesh){
					CargoPortsideMesh->SetStaticMesh(FreighterMeshSet->Categories["CargoPodsPortside"].Variants["Small"].StaticMesh);
					CargoPortsideMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case ECargoPodType::Medium:
				if (FreighterMeshSet->Categories["CargoPodsPortside"].Variants["Medium"].StaticMesh){
					CargoPortsideMesh->SetStaticMesh(FreighterMeshSet->Categories["CargoPodsPortside"].Variants["Medium"].StaticMesh);
					CargoPortsideMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case ECargoPodType::Large:
				if (FreighterMeshSet->Categories["CargoPodsPortside"].Variants["Large"].StaticMesh){
					CargoPortsideMesh->SetStaticMesh(FreighterMeshSet->Categories["CargoPodsPortside"].Variants["Large"].StaticMesh);
					CargoPortsideMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			
		}
		switch (CargoPodStarBoard){
			case ECargoPodType::Small:
				if (FreighterMeshSet->Categories["CargoPodsStarboard"].Variants["Small"].StaticMesh){
					CargoStarboardMesh->SetStaticMesh(FreighterMeshSet->Categories["CargoPodsStarboard"].Variants["Small"].StaticMesh);
					CargoStarboardMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case ECargoPodType::Medium:
				if (FreighterMeshSet->Categories["CargoPodsStarboard"].Variants["Medium"].StaticMesh){
					CargoStarboardMesh->SetStaticMesh(FreighterMeshSet->Categories["CargoPodsStarboard"].Variants["Medium"].StaticMesh);
					CargoStarboardMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case ECargoPodType::Large:
				if (FreighterMeshSet->Categories["CargoPodsStarboard"].Variants["Large"].StaticMesh){
					CargoStarboardMesh->SetStaticMesh(FreighterMeshSet->Categories["CargoPodsStarboard"].Variants["Large"].StaticMesh);
					CargoStarboardMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;	
		}
		switch (Thrusters){
			case EThrusterType::Efficient:
				if (FreighterMeshSet->Categories["Thrusters"].Variants["Efficient"].StaticMesh){
					ThrustersMesh->SetStaticMesh(FreighterMeshSet->Categories["Thrusters"].Variants["Efficient"].StaticMesh);
					ThrustersMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case EThrusterType::Balanced:
				if (FreighterMeshSet->Categories["Thrusters"].Variants["Balanced"].StaticMesh){
					ThrustersMesh->SetStaticMesh(FreighterMeshSet->Categories["Thrusters"].Variants["Balanced"].StaticMesh);
					ThrustersMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case EThrusterType::Powerful:
				if (FreighterMeshSet->Categories["Thrusters"].Variants["Powerful"].StaticMesh){
					ThrustersMesh->SetStaticMesh(FreighterMeshSet->Categories["Thrusters"].Variants["Powerful"].StaticMesh);
					ThrustersMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			
		}

		if (FreighterMeshSet->Categories["Other"].Variants["CommStation"].StaticMesh){
			CommStationMesh->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["CommStation"].StaticMesh);
			CommStationMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}
		if (FreighterMeshSet->Categories["Other"].Variants["PCD"].StaticMesh){
			PCD->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["PCD"].StaticMesh);
			PCD->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}
		if (FreighterMeshSet->Categories["Other"].Variants["Reactor1"].StaticMesh){
			Reactor1->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["Reactor1"].StaticMesh);
			Reactor1->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}
		if (FreighterMeshSet->Categories["Other"].Variants["Reactor2"].StaticMesh){
			Reactor2->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["Reactor2"].StaticMesh);
			Reactor2->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}
		if (FreighterMeshSet->Categories["Other"].Variants["PCD-Cover"].StaticMesh){
			PCDCover->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["PCD-Cover"].StaticMesh);
			PCDCover->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}
		if (FreighterMeshSet->Categories["Other"].Variants["Reactor1-Cover"].StaticMesh){
			Reactor1Cover->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["Reactor1-Cover"].StaticMesh);
			Reactor1Cover->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}
		if (FreighterMeshSet->Categories["Other"].Variants["Reactor2-Cover"].StaticMesh){
			Reactor2Cover->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["Reactor2-Cover"].StaticMesh);
			Reactor2Cover->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}

		if (WeaponsForward){
			WeaponForward = GetWorld()->SpawnActor<AFreighterWeapons>(
				WeaponsForward,
				FTransform::Identity
			);

			SetupWeapon(WeaponForward, HullMesh, "F-LargHardpoint");
		}
		
		if (WeaponsPortside){
			for (int i = 1; i<4; i++){
				AFreighterWeapons* Temp = GetWorld()->SpawnActor<AFreighterWeapons>(
					WeaponsPortside,
					FTransform::Identity
				);
				SetupWeapon(Temp, HullMesh, FName(*FString::Printf(TEXT("L-LargeHardpoint%d"), i)));
				WeaponsLeft.Add(Temp);
			}
		}
		if (WeaponsStarboard){
			for (int i = 1; i<4; i++){
				AFreighterWeapons* Temp = GetWorld()->SpawnActor<AFreighterWeapons>(
					WeaponsStarboard,
					FTransform::Identity
				);
				SetupWeapon(Temp, HullMesh, FName(*FString::Printf(TEXT("R-LargeHardpoint%d"), i)));
				WeaponsRight.Add(Temp);
			}
		}
        
	}
	
}

// Called every frame
void AFreighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!isDead){
		if (Health <= 0.f){
			isDead = true;
			if (Death){
				TArray<FName> Sockets = {"Reactor1Socket","Reactor2Socket","L-LargeHardpoint1"};
				for (int i = 0; i<3; i++){
					FTimerHandle TimerHandle;
					GetWorld()->GetTimerManager().SetTimer(
						TimerHandle,
						[this, Sockets, i]()
						{
							UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),Death,HullMesh->GetSocketLocation(Sockets[i]));
							if (DeathSound){
								UGameplayStatics::PlaySoundAtLocation(
									GetWorld(),
									DeathSound,
									GetActorLocation(),
									1.0f,
									FMath::FRandRange(0.5f, 1.5f)
								);
							}
						},
						.1f+i*2.f*FMath::FRandRange(0.5f, 1.5f),
						false
					);
				}
			}
			FTimerHandle TimerHandle;
		}
	}
	
	if (Shields < MaxShields){
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			[this, DeltaTime]()
			{
				Shields += 50.0f * DeltaTime;
				Shields = FMath::Clamp(Shields, 0.f, MaxShields);
			},
			10.f,
			false
		);
	}
}

// Called to bind functionality to input
void AFreighter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFreighter::SetupWeapon(AFreighterWeapons* Weapon, USkeletalMeshComponent* InHullMesh, FName Socket){
    Weapon->AttachToComponent(
        HullMesh,
        FAttachmentTransformRules::SnapToTargetNotIncludingScale,
        Socket
    );
    Weapon->SetActorScale3D(FVector(0.05f,0.05f,0.05f));
    Weapon->AddActorLocalRotation(FRotator(0.f,180.f,180.f));
	Weapon->OwningFreighter = this;
}

float AFreighter::TakeDamage(
    float DamageAmount,
    FDamageEvent const& DamageEvent,
    AController* EventInstigator,
    AActor* DamageCauser)
{
    if (Shields <= 0.f){
		Health -= DamageAmount;
	}
	else {
		Shields -= DamageAmount*.8f;
	}

    return DamageAmount;
}