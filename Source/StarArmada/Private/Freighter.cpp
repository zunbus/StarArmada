// Fill out your copyright notice in the Description page of Project Settings.


#include "Freighter.h"
#include "FreighterMeshSet.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFreighter::AFreighter()
{
 	HullMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hull Mesh"));
	SetRootComponent(HullMesh);
	
	
	


	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFreighter::BeginPlay()
{
	Super::BeginPlay();
	if (FreighterMeshSet){
		HullMesh->SetSkeletalMesh(FreighterMeshSet->Hull);
	}
	
}

// Called every frame
void AFreighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFreighter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

