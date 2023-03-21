// Fill out your copyright notice in the Description page of Project Settings.


#include "RectangleGrid.h"



// Sets default values
ARectangleGrid::ARectangleGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ARectangleGrid::BeginPlay()
{
	Super::BeginPlay();
	NavGrid2DArray.SetNumZeroed(XGridDimension);
	for (int32 i = 0; i < NavGrid2DArray.Num(); i++) {
		NavGrid2DArray[i].SetNumZeroed(YGridDimension);
	}
	auto ActorLocation = GetActorLocation();
	for (int32 y = 0; y < YGridDimension; y++) {
		for (int32 x = 0; x < XGridDimension; x++) {
			int XPos = (x * GridSpacing) + ActorLocation.X;
			int YPos = (y * GridSpacing) + ActorLocation.Y;
			auto TileType = WaterTile;
			AGridTile* NewTile = GetWorld()->SpawnActor<AGridTile>(TileType, FVector(FIntPoint(XPos, YPos), ActorLocation.Z), FRotator::ZeroRotator);
			NewTile->TileIndex = FIntPoint(XPos, YPos);
			NewTile->SetActorLabel(FString::Printf(TEXT("Tile_%d_%d"), x, y));
			TArray<FName> GridTag;
			GridTag.Add(TEXT("GRID_TILE"));
			NewTile->Tags = GridTag;
			NavGrid2DArray[x][y] = NewTile;
		}
	}

}

// Called every frame
void ARectangleGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

