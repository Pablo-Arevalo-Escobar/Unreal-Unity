// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GridTile.h"
#include "RectangleGrid.generated.h"

UCLASS()
class BATTLESHIP_API ARectangleGrid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARectangleGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "NavGridSetup")
	TSubclassOf<AGridTile> WaterTile;

	UPROPERTY(EditAnywhere, Category = "NavGridSetup")
	TSubclassOf<AGridTile> GrassTile;

	TArray<TArray<AGridTile*>> NavGrid2DArray;

	UPROPERTY(EditAnywhere, Category = "NavGridLayout")
	int32 XGridDimension = 10;

	UPROPERTY(EditAnywhere, Category = "NavGridLayout")
	int32 YGridDimension = 10;

	UPROPERTY(EditAnywhere, Category = "NavGridLayout")
	int GridSpacing = 100;
};
