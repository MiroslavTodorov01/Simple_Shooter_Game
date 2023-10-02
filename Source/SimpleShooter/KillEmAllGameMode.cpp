// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::BeginPlay()
{
    Super::BeginPlay();

    // TArray<AActor*> actors;

    // UGameplayStatics::GetAllActorsOfClass(this, AShooterCharacter::StaticClass(), actors);

    // enemyCount = actors.Num() - 1;
}

void AKillEmAllGameMode::KillPawn(APawn* pawnKilled)
{
    Super::KillPawn(pawnKilled);

    APlayerController* playerController = Cast<APlayerController>(pawnKilled->GetController());

    if (playerController) 
    {
        GameOver(false);

        // Defeat();
    }
    else
    {
        for(AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
        {
            AIController->isDead();

            if (!AIController->isDead()) 
            {
                return;
            }
        }

        GameOver(true);
    }
}

void AKillEmAllGameMode::GameOver(bool bPlayerWinner)
{

    for(AController* controller : TActorRange<AController>(GetWorld()))
    {
        
        bool winner = controller->IsPlayerController() == bPlayerWinner;
        controller->GameHasEnded(controller->GetPawn(),  winner);
    } 
}