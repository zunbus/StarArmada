// Fill out your copyright notice in the Description page of Project Settings.


#include "FreighterWeapons.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AFreighterWeapons::AFreighterWeapons()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	SetRootComponent(Mesh);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFreighterWeapons::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFreighterWeapons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

