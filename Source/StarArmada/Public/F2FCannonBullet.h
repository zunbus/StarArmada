// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "F2FCannonBullet.generated.h"
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class STARARMADA_API AF2FCannonBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AF2FCannonBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* ImpactParticles;

	void Kill();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
