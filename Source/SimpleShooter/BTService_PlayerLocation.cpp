// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
    NodeName = TEXT("Set Player");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (!player) 
    {
        return;
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), player->GetActorLocation());
}