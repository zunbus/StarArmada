// Fill out your copyright notice in the Description page of Project Settings.


#include "F2FCannonBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AF2FCannonBullet::AF2FCannonBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	SetRootComponent(BulletMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
    ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->ProjectileGravityScale = 0.f;

}

// Called when the game starts or when spawned
void AF2FCannonBullet::BeginPlay()
{
	Super::BeginPlay();


	FTimerHandle DieTimer;
	GetWorld()->GetTimerManager().SetTimer(
		DieTimer,
		this,
		&AF2FCannonBullet::Kill,
		30.f,
		false
	);
	
}
void AF2FCannonBullet::Kill(){
	Destroy();
}


// Called every frame
void AF2FCannonBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

