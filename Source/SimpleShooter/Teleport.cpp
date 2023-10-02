// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleport.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATeleport::ATeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	RootComponent = root;

	startPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Start location"));

	startPoint->SetupAttachment(RootComponent);

	startParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("p1"));

	startParticle->SetupAttachment(startPoint);

	endPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("End location"));

	endPoint->SetupAttachment(RootComponent);

	endParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("p2"));

	endParticle->SetupAttachment(endPoint);
}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();

	startPoint->SetVisibility(false);

	endPoint->SetVisibility(false);
}

// Called every frame
void ATeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ifTeleportIsOnCooldown) 
	{
		float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

		currentSeconds -= deltaTime;

		if (FMath::CeilToInt32(currentSeconds) == 0) 
		{
			ifTeleportIsOnCooldown = false;
		}
		else 
		{
			//UE_LOG(LogTemp, Display, TEXT("%d"), FMath::CeilToInt32(currentSeconds));
			return;
		}
	}

	TArray<AActor*> overlappedActors;

	GetOverlappingActors(overlappedActors);

	for(int i = 0; i < overlappedActors.Num(); i++)
	{
		AShooterCharacter* player = Cast<AShooterCharacter>(overlappedActors[i]);

		if (player != nullptr && !ifTeleportIsOnCooldown) 
		{
			player->SetActorLocation(endPoint->GetComponentLocation());

			currentSeconds = timeAfterTeleporting;

			ifTeleportIsOnCooldown = true;
		}
	}
}
