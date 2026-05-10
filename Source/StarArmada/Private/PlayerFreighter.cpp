// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFreighter.h"
#include "FreighterMeshSet.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/Engine.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "FreighterWeapons.h"
#include "Kismet/GameplayStatics.h"
#include "instance.h"



APlayerFreighter::APlayerFreighter()
{
    FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
    FloatingMovement->UpdatedComponent = RootComponent;
    FloatingMovement->Deceleration = 100.f;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bUsePawnControlRotation = false;
    CameraBoom->bEnableCameraLag = true;
    CameraBoom->bEnableCameraRotationLag = true;
    
	PathMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Path Mesh"));
    PathMesh->SetupAttachment(RootComponent);
    PathMesh->SetComponentTickEnabled(true);

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> PathMeshAsset(
        TEXT("/Game/Graphics/Meshes/PFP-Path.PFP-Path")
    );

    if (PathMeshAsset.Succeeded())
    {
        PathMesh->SetSkeletalMesh(PathMeshAsset.Object);
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPClass(
    TEXT("/Game/Graphics/Meshes/ABP_PFP.ABP_PFP")
    );

    if (AnimBPClass.Succeeded())
    {
        PathMesh->SetAnimInstanceClass(AnimBPClass.Class);
    }

	PathMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	PathMesh->InitAnim(true);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("View Camera"));
	Camera ->SetupAttachment(CameraBoom);

    GameInstance = Cast<UInstance>(GetGameInstance());
    
}

void APlayerFreighter::BeginPlay()
{
	Super::BeginPlay();
	

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
            }
        }
    }

    if (FreighterMeshSet){
		CameraBoom->TargetArmLength = FreighterMeshSet->CameraBoomLength;
        CameraBoom->AttachToComponent(
        HullMesh,
        FAttachmentTransformRules(
            EAttachmentRule::SnapToTarget,
            EAttachmentRule::KeepRelative,
            EAttachmentRule::KeepRelative,
            false
        ),
        FreighterMeshSet->CameraBoomSocket
        );
        PathMesh->AttachToComponent(
        HullMesh,
        FAttachmentTransformRules(
            EAttachmentRule::SnapToTarget,
            EAttachmentRule::SnapToTarget,
            EAttachmentRule::SnapToTarget,
            false
        ),
        TEXT("Forward")
        );
        PathMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
        PathMesh->SetRelativeRotation(FRotator(-90.f, 90.f, 180.f));
        PathMesh->SetRelativeScale3D(FVector(0.015, 0.008, 0.008));

        
        
	}


    // Instance Setup

    switch (GameInstance->HangarInst){
			case EHangarType::Innovative:
				if(FreighterMeshSet->Categories["Hangars"].Variants["Innovative"].StaticMesh){
					HangarMesh->SetStaticMesh(FreighterMeshSet->Categories["Hangars"].Variants["Innovative"].StaticMesh);
					HangarMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case EHangarType::Classic:
				if(FreighterMeshSet->Categories["Hangars"].Variants["Classic"].StaticMesh){
					HangarMesh->SetStaticMesh(FreighterMeshSet->Categories["Hangars"].Variants["Classic"].StaticMesh);
					HangarMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case EHangarType::SkyView:
				if(FreighterMeshSet->Categories["Hangars"].Variants["SkyView"].StaticMesh){
					HangarMesh->SetStaticMesh(FreighterMeshSet->Categories["Hangars"].Variants["SkyView"].StaticMesh);
					HangarMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
		}
		switch (GameInstance->BowInst){
			case EBowType::Storage:
				if(FreighterMeshSet->Categories["Bows"].Variants["Storage"].StaticMesh){
					BowMesh->SetStaticMesh(FreighterMeshSet->Categories["Bows"].Variants["Storage"].StaticMesh);
					BowMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case EBowType::Terraformator:
				if(FreighterMeshSet->Categories["Bows"].Variants["Terraformator"].StaticMesh){
					BowMesh->SetStaticMesh(FreighterMeshSet->Categories["Bows"].Variants["Terraformator"].StaticMesh);
					BowMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
		}
		switch (GameInstance->CargoPodPortsideInst){
			case ECargoPodType::Small:
				if (FreighterMeshSet->Categories["CargoPodsPortside"].Variants["Small"].StaticMesh){
					CargoPortsideMesh->SetStaticMesh(FreighterMeshSet->Categories["CargoPodsPortside"].Variants["Small"].StaticMesh);
					CargoPortsideMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case ECargoPodType::Medium:
				if (FreighterMeshSet->Categories["CargoPodsPortside"].Variants["Medium"].StaticMesh){
					CargoPortsideMesh->SetStaticMesh(FreighterMeshSet->Categories["CargoPodsPortside"].Variants["Medium"].StaticMesh);
					CargoPortsideMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case ECargoPodType::Large:
				if (FreighterMeshSet->Categories["CargoPodsPortside"].Variants["Large"].StaticMesh){
					CargoPortsideMesh->SetStaticMesh(FreighterMeshSet->Categories["CargoPodsPortside"].Variants["Large"].StaticMesh);
					CargoPortsideMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			
		}
		switch (GameInstance->CargoPodStarBoardInst){
			case ECargoPodType::Small:
				if (FreighterMeshSet->Categories["CargoPodsStarboard"].Variants["Small"].StaticMesh){
					CargoStarboardMesh->SetStaticMesh(FreighterMeshSet->Categories["CargoPodsStarboard"].Variants["Small"].StaticMesh);
					CargoStarboardMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case ECargoPodType::Medium:
				if (FreighterMeshSet->Categories["CargoPodsStarboard"].Variants["Medium"].StaticMesh){
					CargoStarboardMesh->SetStaticMesh(FreighterMeshSet->Categories["CargoPodsStarboard"].Variants["Medium"].StaticMesh);
					CargoStarboardMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case ECargoPodType::Large:
				if (FreighterMeshSet->Categories["CargoPodsStarboard"].Variants["Large"].StaticMesh){
					CargoStarboardMesh->SetStaticMesh(FreighterMeshSet->Categories["CargoPodsStarboard"].Variants["Large"].StaticMesh);
					CargoStarboardMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;	
		}
		switch (GameInstance->ThrustersInst){
			case EThrusterType::Efficient:
				if (FreighterMeshSet->Categories["Thrusters"].Variants["Efficient"].StaticMesh){
					ThrustersMesh->SetStaticMesh(FreighterMeshSet->Categories["Thrusters"].Variants["Efficient"].StaticMesh);
					ThrustersMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case EThrusterType::Balanced:
				if (FreighterMeshSet->Categories["Thrusters"].Variants["Balanced"].StaticMesh){
					ThrustersMesh->SetStaticMesh(FreighterMeshSet->Categories["Thrusters"].Variants["Balanced"].StaticMesh);
					ThrustersMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			case EThrusterType::Powerful:
				if (FreighterMeshSet->Categories["Thrusters"].Variants["Powerful"].StaticMesh){
					ThrustersMesh->SetStaticMesh(FreighterMeshSet->Categories["Thrusters"].Variants["Powerful"].StaticMesh);
					ThrustersMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
				}
				break;
			
		}

		if (FreighterMeshSet->Categories["Other"].Variants["CommStation"].StaticMesh){
			CommStationMesh->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["CommStation"].StaticMesh);
			CommStationMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}
		if (FreighterMeshSet->Categories["Other"].Variants["PCD"].StaticMesh){
			PCD->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["PCD"].StaticMesh);
			PCD->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}
		if (FreighterMeshSet->Categories["Other"].Variants["Reactor1"].StaticMesh){
			Reactor1->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["Reactor1"].StaticMesh);
			Reactor1->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}
		if (FreighterMeshSet->Categories["Other"].Variants["Reactor2"].StaticMesh){
			Reactor2->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["Reactor2"].StaticMesh);
			Reactor2->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}
		if (FreighterMeshSet->Categories["Other"].Variants["PCD-Cover"].StaticMesh){
			PCDCover->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["PCD-Cover"].StaticMesh);
			PCDCover->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}
		if (FreighterMeshSet->Categories["Other"].Variants["Reactor1-Cover"].StaticMesh){
			Reactor1Cover->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["Reactor1-Cover"].StaticMesh);
			Reactor1Cover->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}
		if (FreighterMeshSet->Categories["Other"].Variants["Reactor2-Cover"].StaticMesh){
			Reactor2Cover->SetStaticMesh(FreighterMeshSet->Categories["Other"].Variants["Reactor2-Cover"].StaticMesh);
			Reactor2Cover->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		}

        WeaponForward->Destroy();

		if (GameInstance->WeaponsForwardInst){
			WeaponForward = GetWorld()->SpawnActor<AFreighterWeapons>(
				WeaponsForward,
				FTransform::Identity
			);

		SetupWeapon(WeaponForward, HullMesh, "F-LargHardpoint");
	}
	
    for (int i = 0; i<3; i++){
        WeaponsLeft[i]->Destroy();
        WeaponsRight[i]->Destroy();
    }

	if (GameInstance->WeaponsPortsideInst){
		for (int i = 1; i<4; i++){
			AFreighterWeapons* Temp = GetWorld()->SpawnActor<AFreighterWeapons>(
				WeaponsPortside,
				FTransform::Identity
			);
			SetupWeapon(Temp, HullMesh, FName(*FString::Printf(TEXT("L-LargeHardpoint%d"), i)));
			WeaponsLeft.Add(Temp);
		}
	}
	if (GameInstance->WeaponsStarboardInst){
		for (int i = 1; i<4; i++){
			AFreighterWeapons* Temp = GetWorld()->SpawnActor<AFreighterWeapons>(
				WeaponsStarboard,
				FTransform::Identity
			);
			SetupWeapon(Temp, HullMesh, FName(*FString::Printf(TEXT("R-LargeHardpoint%d"), i)));
			WeaponsRight.Add(Temp);
		}
	}
}
void APlayerFreighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AddMovementInput(GetActorForwardVector(), CurrentThrottle/100.f);
    if (GetVelocity().Size() >= 10.f){
        AddActorLocalRotation(FRotator(CurrentTurn.Y*-0.001f*(CurrentThrottle/100.f), CurrentTurn.X*0.001f*(CurrentThrottle/100.f), 0.0f));
    }
}


void APlayerFreighter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    
    if (!EnhancedInput) return;

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)){
        EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &APlayerFreighter::Throttle);
        EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &APlayerFreighter::Turn);
        EnhancedInputComponent->BindAction(ToggleFreecamAction, ETriggerEvent::Triggered, this, &APlayerFreighter::ToggleFreeCam);
        EnhancedInputComponent->BindAction(WeaponsLAction, ETriggerEvent::Triggered, this, &APlayerFreighter::SetWeapons3);
        EnhancedInputComponent->BindAction(WeaponsRAction, ETriggerEvent::Triggered, this, &APlayerFreighter::SetWeapons2);
        EnhancedInputComponent->BindAction(WeaponsFAction, ETriggerEvent::Triggered, this, &APlayerFreighter::SetWeapons1);
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &APlayerFreighter::FireWeapons);
    }
    
}

void APlayerFreighter::ToggleFreeCam(const FInputActionValue &Value){
    if(FreeCam){
        FreeCam = false;
        Camera->SetRelativeRotation(FRotator(0.f,0.f,0.f));
    }
    else {
        FreeCam = true;
    }
}

void APlayerFreighter::Throttle(const FInputActionValue &Value){
    float InputValue = Value.Get<float>();
    CurrentThrottle = FMath::Clamp(CurrentThrottle+InputValue*0.5f, 0.0f, 100.0f);
}
void APlayerFreighter::Turn(const FInputActionValue &Value){

    FVector2D InputValue = Value.Get<FVector2D>();

    if(!FreeCam && ActiveWeapons==0){
        CurrentTurn = FVector2D(FMath::Clamp(CurrentTurn.X+InputValue.X*2, -1000.0f, 1000.0f),
                                FMath::Clamp(CurrentTurn.Y+InputValue.Y*2, -1000.0f, 1000.0f));
    }
    else if (ActiveWeapons!=0){
        Camera->AddLocalRotation(FRotator(InputValue.Y, InputValue.X, 0.f));
        Camera->SetRelativeRotation(FRotator(
            FMath::Clamp(Camera->GetRelativeRotation().Pitch, 0.f, 20.f),
            FMath::Clamp(Camera->GetRelativeRotation().Yaw, -45.f, 45.f),
            0.f));
        switch(ActiveWeapons){
            case 1:
                    WeaponForward->Aim = FVector2D(Camera->GetRelativeRotation().Pitch,Camera->GetRelativeRotation().Yaw);
                break;
            case 2:
                for (int i = 0; i<3; i++){
                    WeaponsLeft[i]->Aim = FVector2D(Camera->GetRelativeRotation().Pitch,Camera->GetRelativeRotation().Yaw);
                }
                break;
            case 3:
                for (int i = 0; i<3; i++){
                    WeaponsRight[i]->Aim = FVector2D(Camera->GetRelativeRotation().Pitch,Camera->GetRelativeRotation().Yaw);
                }
                break;
        }
        
    }
    else {
        Camera->AddLocalRotation(FRotator(InputValue.Y, InputValue.X, 0.f));

    }
    
}

void APlayerFreighter::SetWeapons1(const FInputActionValue &Value){
    if (WeaponForward){
        if (ActiveWeapons!=1){
            ActiveWeapons=1;
            CameraBoom->SetRelativeRotation(FRotator(70.f,0.f,0.f));
            CameraBoom->SetRelativeLocation(FVector(0.f,0.f,0.f));
            WeaponForward->Active=true;
            for (int i = 0; i<3; i++){
                WeaponsLeft[i]->Active = false;
                WeaponsRight[i]->Active = false;
            }
        }
        else {
            Camera->SetRelativeRotation(FRotator(0.f,0.f,0.f));

            WeaponForward->Active=false;
            for (int i = 0; i<3; i++){
                WeaponsLeft[i]->Active = false;
                WeaponsRight[i]->Active = false;
            }

            ActiveWeapons=0;
        }
    }
    
}
void APlayerFreighter::SetWeapons2(const FInputActionValue &Value){

    if (!WeaponsLeft.IsEmpty()){
        if (ActiveWeapons!=2){
            CameraBoom->SetRelativeRotation(FRotator(0.f,90.f,90.f));
            CameraBoom->SetRelativeLocation(FVector(0.f,0.f,5.f));

            WeaponForward->Active=false;
            for (int i = 0; i<3; i++){
                WeaponsLeft[i]->Active = true;
                WeaponsRight[i]->Active = false;
            }

            ActiveWeapons=2;
        }
        else {
            CameraBoom->SetRelativeRotation(FRotator(70.f,0.f,0.f));
            CameraBoom->SetRelativeLocation(FVector(0.f,0.f,0.f));
            Camera->SetRelativeRotation(FRotator(0.f,0.f,0.f));

            WeaponForward->Active=false;
            for (int i = 0; i<3; i++){
                WeaponsLeft[i]->Active = false;
                WeaponsRight[i]->Active = false;
            }
            
            ActiveWeapons=0;
        }
    }

    
}
void APlayerFreighter::SetWeapons3(const FInputActionValue &Value){

    if (!WeaponsRight.IsEmpty()){
        if (ActiveWeapons!=3){
            CameraBoom->SetRelativeRotation(FRotator(0.f,-90.f,-90.f));
            CameraBoom->SetRelativeLocation(FVector(0.f,0.f,5.f));

            WeaponForward->Active=false;
            for (int i = 0; i<3; i++){
                WeaponsLeft[i]->Active = false;
                WeaponsRight[i]->Active = true;
            }

            ActiveWeapons=3;
        }
        else {
            CameraBoom->SetRelativeRotation(FRotator(70.f,0.f,0.f));
            CameraBoom->SetRelativeLocation(FVector(0.f,0.f,0.f));
            Camera->SetRelativeRotation(FRotator(0.f,0.f,0.f));

            WeaponForward->Active=false;
            for (int i = 0; i<3; i++){
                WeaponsLeft[i]->Active = false;
                WeaponsRight[i]->Active = false;
            }
            
            ActiveWeapons=0;
        }
    }
    
}

void APlayerFreighter::FireWeapons(const FInputActionValue &Value){
    switch (ActiveWeapons){
        case 0:
            break;
        case 1:
            if(WeaponForward){
                WeaponForward->Fire();
            }
            break;
        case 2:
            if(!WeaponsLeft.IsEmpty()){
                for (int i = 0; i<3; i++){
                    AFreighterWeapons* Weapon = WeaponsLeft[i];

                    FTimerHandle TimerHandle;

                    GetWorld()->GetTimerManager().SetTimer(
                        TimerHandle,
                        [Weapon]()
                        {
                            Weapon->Fire();
                        },
                        (.2f*i)+.1f,
                        false
                    );
                }
            }
            
            break;
        case 3:
            if(!WeaponsRight.IsEmpty()){
                for (int i = 0; i<3; i++){
                    AFreighterWeapons* Weapon = WeaponsRight[i];

                    FTimerHandle TimerHandle;

                    GetWorld()->GetTimerManager().SetTimer(
                        TimerHandle,
                        [Weapon]()
                        {
                            Weapon->Fire();
                        },
                        (.2f*i)+.1f,
                        false
                    );
                }
            }
            
            break;
    }
}