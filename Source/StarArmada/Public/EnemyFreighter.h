// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Freighter.h"
#include "EnemyFreighter.generated.h"



/**
 * 
 */
UCLASS()
class STARARMADA_API AEnemyFreighter : public AFreighter
{
	GENERATED_BODY()

	AEnemyFreighter();

	protected:
		virtual void Tick(float DeltaTime) override;;
	
	public:
		void AimAtTarget(FVector Target);

		UPROPERTY(EditAnywhere)
		class UFloatingPawnMovement* FloatingMovement;

};
