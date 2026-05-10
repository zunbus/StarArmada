// © 2026 Hubert Filas. All Rights Reserved.


#include "F2FCannonBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Freighter.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/DamageType.h"

// Sets default values
AF2FCannonBullet::AF2FCannonBullet()
{
 	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetGenerateOverlapEvents(true);
	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	Collision->SetCollisionResponseToAllChannels(ECR_Overlap);

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->SetupAttachment(Collision);
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	ProjectileMovement->UpdatedComponent = Collision;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->InitialSpeed = 800.f;
}

// Called when the game starts or when spawned
void AF2FCannonBullet::BeginPlay()
{
	Super::BeginPlay();


	Collision->OnComponentBeginOverlap.AddDynamic(this, &AF2FCannonBullet::OnOverlapBegin);
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->bSweepCollision = false;

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
void AF2FCannonBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != Cast<AActor>(Outer) && !OtherActor->IsA(AFreighterWeapons::StaticClass())){
		

		if (ImpactParticles){
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactParticles, GetActorLocation(),GetActorRotation());
		}
		else if (CascadeImpactParticles){
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),CascadeImpactParticles,GetActorLocation());
		}

		if (ImpactSound){
			UGameplayStatics::PlaySoundAtLocation(
				this,
				ImpactSound,
				GetActorLocation()
			);
		}
		
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			GetInstigatorController(),
			this,
			UDamageType::StaticClass()
		);

		Destroy();
	}
	
}

// Called every frame
void AF2FCannonBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

