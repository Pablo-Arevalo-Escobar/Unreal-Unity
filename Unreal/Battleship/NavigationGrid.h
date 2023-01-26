// Fill out your copyright notice in the Description page of Project Settings.
//Grid class that can be used to place items which inherit the GridItem property

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GridTile.h"
#include "NavigationGrid.generated.h"

UCLASS()
class BATTLESHIP_API ANavigationGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANavigationGrid();

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
