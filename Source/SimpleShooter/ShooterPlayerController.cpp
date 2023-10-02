// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    crosshair = CreateWidget(this, crosshairClass);

    if (!crosshair) 
    {
        UE_LOG(LogTemp, Display, TEXT("crosshair null!"));
        return;
    }

    crosshair->AddToViewport();
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    UE_LOG(LogTemp, Display, TEXT("game end!"));

    if (bIsWinner) 
    {
        UUserWidget* winScreen = CreateWidget(this, winScreenClass);

        if (winScreen) 
        {
            winScreen->AddToViewport();
        }
    }
    else
    {
        UUserWidget* loseScreen = CreateWidget(this, loseScreenClass);

        if (loseScreen) 
        {
            loseScreen->AddToViewport();
        }

        crosshair->RemoveFromParent();
    }

    GetWorldTimerManager().SetTimer(timeReset, this, &APlayerController::RestartLevel, timeDelay);
}