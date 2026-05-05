// © 2026 Hubert Filas. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FreighterMeshSet.generated.h"

class USkeletalMesh;
class UStaticMesh;
class AFreighterWeapons;

// -------------------------
// Variant Struct
// -------------------------
USTRUCT(BlueprintType)
struct FFreighterVariant
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UStaticMesh* StaticMesh = nullptr;
};

// -------------------------
// Category Struct
// -------------------------
USTRUCT(BlueprintType)
struct FFreighterCategory
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TMap<FString, FFreighterVariant> Variants;
};

// -------------------------
// Main Data Asset
// -------------------------
UCLASS(BlueprintType)
class STARARMADA_API UFreighterMeshSet : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:

    // Main hull skeletal mesh
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    USkeletalMesh* Hull = nullptr;

    // Camera settings
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float CameraBoomLength = 100.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FName CameraBoomSocket = TEXT("");

    // Category → Variant → Mesh
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TMap<FString, FFreighterCategory> Categories;

    // Constructor initializes all category/variant keys
    UFreighterMeshSet();
};
