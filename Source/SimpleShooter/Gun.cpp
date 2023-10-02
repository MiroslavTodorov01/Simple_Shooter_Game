// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	comp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	RootComponent = comp;

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	ammo = maxAmmo;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGun::AmmoCheck() const
{
	return ammo > 0;
}

void AGun::Reload()
{
	ammo = maxAmmo;
}

void AGun::pullTrigger()
{
	if (!AmmoCheck()) 
	{
		return;
	}


	UGameplayStatics::SpawnEmitterAttached(shootParticle, mesh, TEXT("MuzzleFlashSocket"));

	UGameplayStatics::SpawnSoundAttached(shootSound, mesh, TEXT("MuzzleFlashSocket"));

	FHitResult hit;

	FRotator characterRotation;

	bool ifHit = GunTrace(characterRotation, hit);

	if (ifHit) 
	{
		// DrawDebugPoint(GetWorld(), hit.Location, 20, FColor::Green, true);

		if (hitParticle != nullptr) 
		{	
			FVector shootDirection = -characterRotation.Vector();

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticle, hit.Location, shootDirection.Rotation(), true);

			UGameplayStatics::PlaySoundAtLocation(this, hitSound, hit.GetActor()->GetActorLocation());

			if (hit.GetActor()) 
			{
				FPointDamageEvent damageEvent = FPointDamageEvent(damage, hit, shootDirection, nullptr);

				AController* characterController = GetOwnerController();
				
				hit.GetActor()->TakeDamage(damage, damageEvent, characterController, this);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("hit is null!!"));
	}

	ammo--; 
}

bool AGun::GunTrace(FRotator& characterRotation, FHitResult& hit)
{	
	AController* ownerController = GetOwnerController();

	if (!ownerController) 
	{
		UE_LOG(LogTemp, Warning, TEXT("controller is null!!"));
		return false;
	}

	FVector characterLocation;

	SetPlayerView(characterLocation, characterRotation, ownerController);

	FVector end = characterLocation + characterRotation.Vector() * shootDistance;

	FCollisionQueryParams params;

	params.AddIgnoredActor(this);

	params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(hit, characterLocation, end, ECollisionChannel::ECC_GameTraceChannel1, params);
}

void AGun::SetPlayerView(FVector& location, FRotator& rotation, AController* characterController)
{
	characterController->GetPlayerViewPoint(location, rotation);
}

AController* AGun::GetOwnerController()
{
	APawn* characterPawn = Cast<APawn>(GetOwner());

	if (!characterPawn) 
	{
		UE_LOG(LogTemp, Warning, TEXT("pawn is null!!"));
		return nullptr;
	}
	return characterPawn->GetController();
}