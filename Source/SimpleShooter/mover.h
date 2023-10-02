// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLESHOOTER_API Umover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Umover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// UPROPERTY(EditAnywhere)
	// float speed = 2.0f;	

	UPROPERTY(EditAnywhere)
	float distance;

	UPROPERTY(EditAnywhere)
	float moveValue;

	UPROPERTY(VisibleAnywhere)
	float currentDistance;

	FVector startPosition;

	FVector endPosition;

	// UPROPERTY(VisibleAnywhere)
	// float test;
};
