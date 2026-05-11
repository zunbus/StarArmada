// © Hubert Filas 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FreighterWeapons.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;
class AFreighter;
class AF2FCannonBullet;
class UCameraShakeBase;
class USoundBase;

UCLASS()
class STARARMADA_API AFreighterWeapons : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFreighterWeapons();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* AimMesh;

	

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* FireParticles;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AF2FCannonBullet> Bullet;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly)
	float CoolDown = 0.f;

	void Release();

	UPROPERTY(EditDefaultsOnly)
	bool locked = false;

	
	UPROPERTY(EditAnywhere, Category = "Camera")
	TSubclassOf<UCameraShakeBase> CameraShakeClass;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	FVector2D Aim = FVector2D(0.f,0.f);

	UPROPERTY(BlueprintReadOnly)
	bool Active = false;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Fire();
	AFreighter* OwningFreighter;

};
