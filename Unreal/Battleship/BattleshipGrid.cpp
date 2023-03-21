// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleshipGrid.h"

void ABattleshipGrid::BeginPlay()
{
    Super::BeginPlay();
    PlayerShipsArray.SetNumZeroed(NumberOfShips);

    auto ActorLocation = GetActorLocation();

    for (int i = 0; i < NumberOfShips; i++) {
        //Convert from index to tile_pos

        //NOTE:: ASSUMING X DIMENSION == YDIMENSION
        int XIndex = i % XGridDimension;
        int YIndex = i % YGridDimension;
        auto Location = NavGrid2DArray[XIndex][YIndex]->GetActorLocation();
        auto ShipType = SizeOneShip;
        AShip* NewShip = GetWorld()->SpawnActor<AShip>(SizeOneShip, FVector(Location.X, Location.Y + YOffset, Location.Z + ZOffset), FRotator::ZeroRotator);
        NewShip->ShipType = EShipType::ONE_TILE;
        NewShip->SetActorLabel(FString::Printf(TEXT("SHIP_%d"), i));



        //If ship size == SizeOneShip
        /*
        * z displacement = 5;
        * y displacement = 50;
        */


        //If ship size == SizeTwoShip
        /*
        * z displacement = 5;
        * y displacement = 50;
        */

        //If ship size == SizeThreeShip
        /*
        * y offset = 100;
        */

        PlayerShipsArray[i] = NewShip;
    }
}

void ABattleshipGrid::MoveShip(AShip& Ship, AGridTile& DestinationTile)
{
    auto Location = DestinationTile.GetActorLocation();
    Ship.SetActorLocation(FVector(Location.X, Location.Y + YOffset, Location.Z + ZOffset));

}

void ABattleshipGrid::RotateShip(AShip& Ship, bool Clockwise)
{
    int direction = Clockwise ? 1 : -1;
    FRotator Rotator = Ship.GetActorRotation();
    Rotator.Yaw += 90.0f * direction;
    Ship.SetActorRotation(Rotator);
}

void ABattleshipGrid::RotateAllShips(float degree)
{
    for (AShip* ship : PlayerShipsArray) {
        FRotator Rotator = ship->GetActorRotation();
        Rotator.Yaw += degree;
        ship->SetActorRotation(Rotator);
    }
}
