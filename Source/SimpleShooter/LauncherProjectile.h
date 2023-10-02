// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LauncherProjectile.generated.h"

UCLASS()
class SIMPLESHOOTER_API ALauncherProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALauncherProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* particleAmmo;
	
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* moveComponent;

	UPROPERTY(EditAnywhere)
	float damage;

	UPROPERTY(EditAnywhere)
	UParticleSystem* explosion;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
