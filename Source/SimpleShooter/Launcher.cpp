// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"
#include "LauncherProjectile.h"

// Sets default values
ALauncher::ALauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(root);

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	mesh->SetupAttachment(root);

	projectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile spawn point"));

	projectileSpawn->SetupAttachment(mesh);
}

// Called when the game starts or when spawned
void ALauncher::BeginPlay()
{
	Super::BeginPlay();
	
	ammo = maxAmmo;
}

// Called every frame
void ALauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALauncher::pullTrigger()
{
	if (ammo == 0) 
	{
		return;
	}

	if (!projectileClass) 
	{
		UE_LOG(LogTemp, Warning, TEXT("projectile not set!"));
		return;
	}
	
	APawn* characterPawn = Cast<APawn>(GetOwner());

	if (!characterPawn) 
	{
		UE_LOG(LogTemp, Warning, TEXT("launcher pawn is null"));
		return;
	}

	ALauncherProjectile* projectile = GetWorld()->SpawnActor<ALauncherProjectile>(projectileClass, projectileSpawn->GetComponentLocation(), characterPawn->GetControlRotation());

	projectile->SetOwner(GetOwner());

	ammo--;
}

void ALauncher::Reload()
{
	ammo = maxAmmo;
}