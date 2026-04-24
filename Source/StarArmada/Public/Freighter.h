// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Freighter.generated.h"

class UFreighterMeshSet;


UCLASS()
class STARARMADA_API AFreighter : public APawn
{
	GENERATED_BODY()

public:
	AFreighter();

protected:
	UPROPERTY(EditDefaultsOnly)
	UFreighterMeshSet* FreighterMeshSet;
	USkeletalMeshComponent* HullMesh;

	

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
