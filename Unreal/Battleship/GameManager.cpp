// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AGameManager::run()
{
}

void AGameManager::SetTarget(AActor* NewTarget)
{
    this->target = NewTarget;
}

AActor* AGameManager::GetTarget()
{
    return target;
}


void AGameManager::FireAtTarget_Implementation()
{
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
    FVector ActorLocation = GetActorLocation();
    FVector Location1 = FVector(FIntPoint(ActorLocation.X, ActorLocation.Y), 0);
    FVector Location2 = FVector(FIntPoint(ActorLocation.X, ActorLocation.Y+1500), 0);
    player1Grid = GetWorld()->SpawnActor<ABattleshipGrid>(gridBlueprint, Location1 , FRotator::ZeroRotator);  	
    player1Grid->SetActorLabel(FString::Printf(TEXT("Grid_1")));

    player2Grid = GetWorld()->SpawnActor<ABattleshipGrid>(gridBlueprint, Location2 , FRotator::ZeroRotator); 
    player2Grid->RotateAllShips(180.0);
    player2Grid->SetActorLabel(FString::Printf(TEXT("Grid_2")));
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

