// © Hubert Filas 2026. All Rights Reserved.


#include "Instance.h"
#include "GameFramework/GameUserSettings.h"
#include "Engine/Engine.h"

void UInstance::Init()
{
    Super::Init();

    GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
    {
        if (!GEngine)
        {
            return;
        }

        UGameUserSettings* Settings = GEngine->GetGameUserSettings();
        if (!Settings)
        {
            return;
        }


        Settings->RunHardwareBenchmark();
        Settings->ApplyHardwareBenchmarkResults();


        Settings->ApplySettings(false);
    });
}