// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void pullTrigger();

	void Reload();

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* comp;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mesh;

	UPROPERTY(EditAnywhere);
	UParticleSystem* shootParticle;

	UPROPERTY(EditAnywhere);
	UParticleSystem* hitParticle;

	UPROPERTY(EditAnywhere)
	USoundBase* shootSound;

	UPROPERTY(EditAnywhere)
	USoundBase* hitSound;
	
	UPROPERTY(EditAnywhere)
	float shootDistance = 1000;

	UPROPERTY(EditAnywhere)
	float damage = 10;

	bool GunTrace(FRotator& characterRotation, FHitResult& hit);

	void SetPlayerView(FVector& location, FRotator& rotation, AController* characterController);

	bool AmmoCheck() const;

	AController* GetOwnerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 maxAmmo;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 ammo;
};
