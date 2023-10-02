// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) override;

protected:

	virtual void BeginPlay() override;
private:

	UPROPERTY(EditAnywhere)
	float timeDelay = 5.f;

	FTimerHandle timeReset;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> loseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> winScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> crosshairClass;

	UUserWidget* crosshair;
};
