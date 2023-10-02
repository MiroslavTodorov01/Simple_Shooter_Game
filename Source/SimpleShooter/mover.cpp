// Fill out your copyright notice in the Description page of Project Settings.


#include "mover.h"

// Sets default values for this component's properties
Umover::Umover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Umover::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	currentDistance = 0;

	startPosition = GetOwner()->GetActorLocation();

	endPosition =GetOwner()->GetActorLocation();

	endPosition.Z += distance;


}


// Called every frame
void Umover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector nextLocation = GetOwner()->GetActorLocation();

	//nextLocation.Z += moveValue * DeltaTime * speed; 

	nextLocation.Z += moveValue * DeltaTime; 

	//test = moveValue * DeltaTime * speed;

	GetOwner()->SetActorLocation(nextLocation);

	//currentDistance += abs(moveValue * DeltaTime * speed);
	
	currentDistance += abs(moveValue * DeltaTime);
	
	if (currentDistance >= distance)
	{
		currentDistance = 0;

		if (moveValue > 0) 
		{
			GetOwner()->SetActorLocation(endPosition);
		}
		else
		{
			GetOwner()->SetActorLocation(startPosition);
		}

		moveValue = -moveValue;
	}
}

