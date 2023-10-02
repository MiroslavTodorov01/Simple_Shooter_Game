// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
class ALauncher;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	bool isDeath() const;

	UFUNCTION(BlueprintCallable)
	float GetPlayerHealthWithPercentage() const;

	void fire();

	UPROPERTY(BlueprintReadOnly)
	int32 weaponIndex;

private:

	void moveLR(float value);

	void moveFB(float value);

	void moveCursorX(float value);

	void upDown(float value);

	void jump();

	void Reload();

	void SwitchToRifal();

	void SwitchToLauncher();

	UPROPERTY(EditAnywhere)
	float speed;

	UPROPERTY(EditAnywhere)
	float rotationRate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> gunClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ALauncher> launcherClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	AGun* rifal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	ALauncher* launcher;

	UPROPERTY(EditAnywhere)
	float maxHealth;

	UPROPERTY(VisibleAnywhere)
	float health;


};
