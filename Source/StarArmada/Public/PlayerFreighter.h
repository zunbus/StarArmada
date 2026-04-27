// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Freighter.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerFreighter.generated.h"
class USpringArmComponent;
class UCameraComponent;
class USplineComponent;
class USplineMeshComponent;
class AFreighterWeapons;

/**
 * 
 */
UCLASS()
class STARARMADA_API APlayerFreighter : public AFreighter
{
	GENERATED_BODY()
	
	protected:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		class UInputAction* ThrottleAction;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		class UInputAction* TurnAction;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		class UInputAction* ToggleFreecamAction;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		class UInputAction* WeaponsLAction;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		class UInputAction* WeaponsRAction;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		class UInputAction* WeaponsFAction;

		virtual void BeginPlay() override;
		virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

		UPROPERTY(EditAnywhere)
		class UFloatingPawnMovement* FloatingMovement;

		UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CameraBoom;
		UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;
		UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* PathMesh;
	private:
		void Throttle(const FInputActionValue &Value);
		void Turn(const FInputActionValue &Value);
		void ToggleFreeCam(const FInputActionValue &Value);
		void SetWeapons1(const FInputActionValue &Value);
		void SetWeapons2(const FInputActionValue &Value);
		void SetWeapons3(const FInputActionValue &Value);
		void SetupWeapon(AFreighterWeapons* Weapon, USkeletalMeshComponent* InHullMesh, FName Socket);
		bool FreeCam = false;
		int ActiveWeapons = 0;

		TArray<AFreighterWeapons*> WeaponsLeft;
        TArray<AFreighterWeapons*> WeaponsRight;
		AFreighterWeapons* WeaponForward;

	public:
		virtual void Tick(float DeltaTime) override;
		APlayerFreighter();
		UPROPERTY(BlueprintReadOnly)
		FVector2D CurrentTurn = FVector2D(0.f, 0.f);
		UPROPERTY(BlueprintReadOnly)
		float CurrentThrottle = 0.f;
		
};
