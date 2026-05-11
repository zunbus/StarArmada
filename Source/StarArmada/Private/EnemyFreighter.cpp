// © Hubert Filas 2026. All Rights Reserved.


#include "EnemyFreighter.h"
#include "Freighter.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/FloatingPawnMovement.h"



AEnemyFreighter::AEnemyFreighter(){
    FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
    FloatingMovement->UpdatedComponent = RootComponent;
    FloatingMovement->Deceleration = 100.f;

}

void AEnemyFreighter::Tick(float DeltaTime){
    Super::Tick(DeltaTime);


    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (PlayerPawn->IsA(AFreighter::StaticClass())){
        AimAtTarget(PlayerPawn->GetActorLocation());
    }

    
}

void AEnemyFreighter::AimAtTarget(FVector Target) // Runs on silver duct tape and dreams
{
    auto ComputeAim = [this](AActor* Weapon, FVector Target) -> FVector2D
    {
        FVector LocalDir = Weapon->GetActorTransform().InverseTransformPosition(Target);

        float Pitch = FMath::RadiansToDegrees(FMath::Atan2(LocalDir.Z, LocalDir.X));


        return FVector2D(Pitch*0.3f, 0.f);
    };

    if (WeaponForward)
        WeaponForward->Aim = ComputeAim(WeaponForward, Target);

    for (int i = 0; i < 3; i++)
    {
        if (WeaponsLeft[i])
            WeaponsLeft[i]->Aim = ComputeAim(WeaponsLeft[i], Target);

        if (WeaponsRight[i])
            WeaponsRight[i]->Aim = ComputeAim(WeaponsRight[i], Target);
    }
}