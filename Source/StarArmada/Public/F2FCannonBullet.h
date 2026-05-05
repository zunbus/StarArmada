// © 2026 Hubert Filas. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "F2FCannonBullet.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class UParticleSystem;
class USphereComponent;
class AFreighter;
class USoundBase;

UCLASS()
class STARARMADA_API AF2FCannonBullet : public AActor
{
    GENERATED_BODY()
    
public: 
    AF2FCannonBullet();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly)
    UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditDefaultsOnly)
    USphereComponent* Collision;

    

    UPROPERTY(EditDefaultsOnly)
    UNiagaraSystem* ImpactParticles;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ImpactSound;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult& SweepResult);

    void Kill();

public: 
    virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditDefaultsOnly)
    UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* CascadeImpactParticles;

	AFreighter* Outer;
};
