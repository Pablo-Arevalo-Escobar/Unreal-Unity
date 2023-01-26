// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleshipGrid.h"

void ABattleshipGrid::BeginPlay()
{
    Super::BeginPlay();
    PlayerShipsArray.SetNumZeroed(NumberOfShips);

    auto ActorLocation = GetActorLocation();

    for (int i = 0; i < NumberOfShips; i++) {
        //TODO::CHECK FOR NULL
        //Convert from index to tile_pos

        //NOTE:: ASSUMING X DIMENSION == YDIMENSION
        int XIndex = i % XGridDimension;
        int YIndex = i % YGridDimension;
        auto Location = NavGrid2DArray[XIndex][YIndex]->GetActorLocation();
        auto ShipType = SizeOneShip;
        AShip* NewShip = GetWorld()->SpawnActor<AShip>(SizeOneShip, FVector(Location.X,Location.Y,Location.Z+ ZOffset), FRotator::ZeroRotator);
        NewShip->ShipType= EShipType::ONE_TILE;
        NewShip->SetActorLabel(FString::Printf(TEXT("SHIP_%d"), i));
        PlayerShipsArray[i] = NewShip;
    }
}

void ABattleshipGrid::MoveShip(AShip& Ship, AGridTile& DestinationTile)
{
    auto Location = DestinationTile.GetActorLocation();
    Ship.SetActorLocation(FVector(Location.X, Location.Y, Location.Z + ZOffset));
    
}
