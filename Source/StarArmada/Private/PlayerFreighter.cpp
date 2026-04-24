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
}
void APlayerFreighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    GEngine->AddOnScreenDebugMessage(
    1,
    0.f,
    FColor::Cyan,
    FString::Printf(TEXT("CurrentThrottle: %.2f"), CurrentThrottle)
    );
    AddMovementInput(GetActorForwardVector(), CurrentThrottle/100.f);
    if (GetVelocity().Size() >= 10.f){
        AddActorLocalRotation(FRotator(CurrentTurn.Y*-0.0001f, CurrentTurn.X*0.0001f, 0.0f));
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
    }
    else {
        Camera->AddLocalRotation(FRotator(InputValue.Y, InputValue.X, 0.f));

    }
    
}

void APlayerFreighter::SetWeapons1(const FInputActionValue &Value){
    if (ActiveWeapons!=1){
        ActiveWeapons=1;
        CameraBoom->SetRelativeRotation(FRotator(70.f,0.f,0.f));
        CameraBoom->SetRelativeLocation(FVector(0.f,0.f,0.f));
    }
    else {
        Camera->SetRelativeRotation(FRotator(0.f,0.f,0.f));
        ActiveWeapons=0;
    }
}
void APlayerFreighter::SetWeapons2(const FInputActionValue &Value){

    if (ActiveWeapons!=2){
        CameraBoom->SetRelativeRotation(FRotator(0.f,90.f,90.f));
        CameraBoom->SetRelativeLocation(FVector(0.f,0.f,5.f));

        ActiveWeapons=2;
    }
    else {
        CameraBoom->SetRelativeRotation(FRotator(70.f,0.f,0.f));
        CameraBoom->SetRelativeLocation(FVector(0.f,0.f,0.f));
        Camera->SetRelativeRotation(FRotator(0.f,0.f,0.f));
        
        ActiveWeapons=0;
    }
}
void APlayerFreighter::SetWeapons3(const FInputActionValue &Value){

    if (ActiveWeapons!=3){
        CameraBoom->SetRelativeRotation(FRotator(0.f,-90.f,-90.f));
        CameraBoom->SetRelativeLocation(FVector(0.f,0.f,5.f));

        ActiveWeapons=3;
    }
    else {
        CameraBoom->SetRelativeRotation(FRotator(70.f,0.f,0.f));
        CameraBoom->SetRelativeLocation(FVector(0.f,0.f,0.f));
        Camera->SetRelativeRotation(FRotator(0.f,0.f,0.f));
        
        ActiveWeapons=0;
    }
}