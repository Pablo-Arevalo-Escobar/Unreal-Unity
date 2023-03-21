// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RectangleGrid.h"
#include "Ship.h"
#include "BattleshipGrid.generated.h"

/**
 *
 */
UCLASS()
class BATTLESHIP_API ABattleshipGrid : public ARectangleGrid
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void MoveShip(AShip& Ship, AGridTile& DestinationTile);
	void RotateShip(AShip& Ship, bool Clockwise);
	void RotateAllShips(float degree);
protected:
	//int NumberOfSizeThreeShips = 3;
	//int NumberOfSizeTwoShips = 2;
	//int NumberOfSizeOneShips = 2;

	UPROPERTY(EditAnywhere)
	int NumberOfShips = 10;

	TArray<AShip*> PlayerShipsArray;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AShip> SizeOneShip;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AShip> SizeTwoShip;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AShip> SizeThreeShip;

private:
	UPROPERTY(EditAnywhere)
	float ZOffset = -50;
	UPROPERTY(EditAnywhere)
	float YOffset = 20;;
};
