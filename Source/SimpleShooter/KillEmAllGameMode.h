// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void KillPawn(APawn* pawnKilled);

	UFUNCTION(BlueprintImplementableEvent)
	void Defeat();

	void GameOver(bool bPlayerWinner);

	//int32 enemyCount;
};
