// © Hubert Filas 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Freighter.h"
#include "Instance.generated.h"

class UGameInstance;

/**
 * 
 */
UCLASS()
class STARARMADA_API UInstance : public UGameInstance
{
	GENERATED_BODY()
	
	public:
		UPROPERTY(EditDefaultsOnly, Category="Configuration|Freighter Customization", BlueprintReadWrite)
		TSubclassOf<AFreighterWeapons> WeaponsPortsideInst;

		UPROPERTY(EditDefaultsOnly, Category="Configuration|Freighter Customization", BlueprintReadWrite)
		TSubclassOf<AFreighterWeapons> WeaponsStarboardInst;

		UPROPERTY(EditDefaultsOnly, Category="Configuration|Freighter Customization", BlueprintReadWrite)
		TSubclassOf<AFreighterWeapons> WeaponsForwardInst;

		UPROPERTY(EditAnywhere, Category="Configuration|Freighter Customization", BlueprintReadWrite)
		EHangarType HangarInst;

		UPROPERTY(EditAnywhere, Category="Configuration|Freighter Customization", BlueprintReadWrite)
		EBowType BowInst;

		UPROPERTY(EditAnywhere, Category="Configuration|Freighter Customization", BlueprintReadWrite)
		ECargoPodType CargoPodPortsideInst;

		UPROPERTY(EditAnywhere, Category="Configuration|Freighter Customization", BlueprintReadWrite)
		ECargoPodType CargoPodStarBoardInst;

		UPROPERTY(EditAnywhere, Category="Configuration|Freighter Customization", BlueprintReadWrite)
		EThrusterType ThrustersInst;

		


};
