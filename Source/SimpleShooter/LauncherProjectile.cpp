// Fill out your copyright notice in the Description page of Project Settings.


#include "LauncherProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "ShooterCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ALauncherProjectile::ALauncherProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Mesh"));

	SetRootComponent(mesh);

	particleAmmo = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Ammo"));

	particleAmmo->SetupAttachment(mesh);

	moveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComp"));

	moveComponent->UpdatedComponent = mesh;

	moveComponent->MaxSpeed = 2000;

	moveComponent->InitialSpeed = 20000;

	moveComponent->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void ALauncherProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	mesh->OnComponentHit.AddDynamic(this, &ALauncherProjectile::OnHit);
}

// Called every frame
void ALauncherProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALauncherProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherActor) 
	{
		FRadialDamageEvent damageEvent = FRadialDamageEvent();

		FRadialDamageParams damageParams = FRadialDamageParams(damage, 200.f);

		damageEvent.Origin = HitComp->GetComponentLocation();

		damageEvent.Params = damageParams;

		// FVector shootDirection = -GetOwner()->GetActorRotation().Vector();

		// FPointDamageEvent damageEvent = FPointDamageEvent(damage, Hit, shootDirection, nullptr);

		APawn* characterPawn = Cast<APawn>(GetOwner());

		if (!characterPawn) 
		{
			UE_LOG(LogTemp, Warning, TEXT("character pawn from launcherProjectile null!!"));
			return;
		}

		//DrawDebugSphere(GetWorld(), HitComp->GetComponentLocation(), 200.f, 20, FColor::Red, false, 1);	
		
		TArray<AActor*> ActorsThatBeenHit;

		UGameplayStatics::ApplyRadialDamage(this, damage, damageEvent.Origin, 200.f, nullptr, ActorsThatBeenHit, GetOwner(), characterPawn->GetController(), true);

		if (explosion) 
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, explosion, HitComp->GetComponentLocation(), FRotator(0), FVector(100));
		}
	}

	Destroy();
}