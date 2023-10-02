// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Launcher.generated.h"

UCLASS()
class SIMPLESHOOTER_API ALauncher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALauncher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void pullTrigger();

	void Reload();

private:	
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* root;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* projectileSpawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ALauncherProjectile> projectileClass;

	UPROPERTY(EditAnywhere)
	int32 maxAmmo = 4;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 ammo;
};
