// © 2026 Hubert Filas. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FreighterWeapons.h"
#include "Freighter.generated.h"


class UFreighterMeshSet;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class UBoxComponent;
class USoundBase;


UENUM(BlueprintType)
enum class EHangarType : uint8
{
    Innovative,
    Classic,
    SkyView
};

UENUM(BlueprintType)
enum class EBowType : uint8
{
    Storage,
    Terraformator
};

UENUM(BlueprintType)
enum class ECargoPodType : uint8
{
    Small,
    Medium,
    Large
};

UENUM(BlueprintType)
enum class EThrusterType : uint8
{
    Efficient,
    Balanced,
    Powerful
};

UCLASS()
class STARARMADA_API AFreighter : public APawn
{
    GENERATED_BODY()

public:
    AFreighter();

protected:

    // The mesh set that defines all freighter parts
    UPROPERTY(EditDefaultsOnly, Category="Configuration|Freighter Customization")
    UFreighterMeshSet* FreighterMeshSet;

    // Root skeletal mesh (the hull)
    UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* HullMesh;

    // All attached static meshes
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* HangarMesh;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BowMesh;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* CargoPortsideMesh;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* CargoStarboardMesh;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* ThrustersMesh;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* CommStationMesh;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PCD;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Reactor1;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Reactor2;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PCDCover;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Reactor1Cover;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Reactor2Cover;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* Collision;

	void SetupWeapon(AFreighterWeapons* Weapon, USkeletalMeshComponent* InHullMesh, FName Socket);



protected:
    virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Configuration|Freighter Customization")
    TSubclassOf<AFreighterWeapons> WeaponsPortside;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Configuration|Freighter Customization")
    TSubclassOf<AFreighterWeapons> WeaponsStarboard;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Configuration|Freighter Customization")
    TSubclassOf<AFreighterWeapons> WeaponsForward;

	UPROPERTY(EditAnywhere, Category="Configuration|Freighter Customization")
	EHangarType Hangar;

	UPROPERTY(EditAnywhere, Category="Configuration|Freighter Customization")
	EBowType Bow;

	UPROPERTY(EditAnywhere, Category="Configuration|Freighter Customization")
	ECargoPodType CargoPodPortside;

	UPROPERTY(EditAnywhere, Category="Configuration|Freighter Customization")
	ECargoPodType CargoPodStarBoard;

	UPROPERTY(EditAnywhere, Category="Configuration|Freighter Customization")
	EThrusterType Thrusters;

    virtual float TakeDamage(
        float DamageAmount,
        struct FDamageEvent const& DamageEvent,
        AController* EventInstigator,
        AActor* DamageCauser
    ) override;

    UPROPERTY(EditAnywhere, Category="Configuration|Health", BlueprintReadOnly)
    float MaxShields = 1000.f;
    UPROPERTY(EditAnywhere, Category="Configuration|Health", BlueprintReadOnly)
    float MaxHealth = 1000.f;

    

    UPROPERTY(EditAnywhere, Category="Configuration|Particles")
    UParticleSystem* Death;
    UPROPERTY(EditAnywhere, Category="Configuration")
    USoundBase* DeathSound;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(BlueprintReadOnly)
	TArray<AFreighterWeapons*> WeaponsLeft;
    UPROPERTY(BlueprintReadOnly)
    TArray<AFreighterWeapons*> WeaponsRight;
    UPROPERTY(BlueprintReadOnly)
	AFreighterWeapons* WeaponForward;

    UPROPERTY(BlueprintReadOnly)
    float Shields = MaxShields;
    UPROPERTY(BlueprintReadOnly)
    float Health = MaxHealth;


    UPROPERTY(BlueprintReadOnly)
    bool isDead = false;
};
