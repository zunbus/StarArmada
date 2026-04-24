// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FreighterMeshSet.generated.h"


class USkeletalMesh;
/**
 * 
 */
UCLASS()
class STARARMADA_API UFreighterMeshSet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	public:
		UPROPERTY(EditDefaultsOnly)
		USkeletalMesh* Hull;
		UPROPERTY(EditDefaultsOnly)
		float CameraBoomLength = 100.f;
		UPROPERTY(EditDefaultsOnly)
		FName CameraBoomSocket = TEXT("");
};
