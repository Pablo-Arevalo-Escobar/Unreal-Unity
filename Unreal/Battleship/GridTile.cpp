// Fill out your copyright notice in the Description page of Project Settings.


#include "GridTile.h"

// Sets default values
AGridTile::AGridTile()
{
    PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
    TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
    TileMesh->SetupAttachment(RootComponent);
}

void AGridTile::BeginPlay()
{
    Super::BeginPlay();
    FScriptDelegate DelegateSubscriber;
    DelegateSubscriber.BindUFunction(this, "OnClicked");
    TileMesh->OnClicked.Add(DelegateSubscriber);

}



void AGridTile::Select_Implementation(bool IsSelected)
{
    OnSelectedTrigger.Broadcast(IsSelected);
}

void AGridTile::OnClicked(AActor* TouchedActor, FKey ButtonPressed)
{
    //this->OnSelectedTrigger.Broadcast();

}



void AGridTile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

