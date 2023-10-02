// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    mainPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (!AIBTree) 
    {
        UE_LOG(LogTemp, Display, TEXT("behavior tree null!"));
        return;
    }

    RunBehaviorTree(AIBTree);

    previousLocation = GetPawn()->GetActorLocation();

    GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), previousLocation);

}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    
}

bool AShooterAIController::isDead()
{
    AShooterCharacter* AI = Cast<AShooterCharacter>(GetPawn());

    return AI->isDeath();
}