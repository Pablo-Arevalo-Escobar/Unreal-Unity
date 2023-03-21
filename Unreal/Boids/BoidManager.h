// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "BoidManager.generated.h"

UENUM()
enum class ESimMode : uint8 {
	INVALID,
	_2D,
	_3D,
	MAX UMETA(Hidden)
};

UCLASS()
class BOIDS_API ABoidManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoidManager();
	~ABoidManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AlignmentAndCohesion();
	void Separation(int Index);

	void RandomWalk(int Index);
	void TimeIntegration(int Index, float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "BoidSimParameter")
	UInstancedStaticMeshComponent* InstancedMesh;

	UPROPERTY(EditAnywhere, Category = "BoidParameter")
	TSubclassOf<ABoid> BoidForm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BoidSimParameter")
	ESimMode SimMode = ESimMode::_3D;

	UPROPERTY(EditAnywhere, Category = "BoidManagerParameter")
	int32 NumberOfBoids;

	UPROPERTY(EditAnywhere, Category = "BoidManagerParameter")
	float NoiseScale;

	UPROPERTY(EditAnywhere, Category = "BoidSimParameter")
	float Scale = 1.0f;

	UPROPERTY(EditAnywhere, Category = "BoidSimParameter")
	float Speed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "BoidSimParameter")
	float BiasTime = 5.0f;

	UPROPERTY(EditAnywhere, Category = "BoidSimParameter")
	float GroupRadius = 100.0f;

	UPROPERTY(EditAnywhere, Category = "BoidSimParameter")
	float SimMode2D_ZIndex = 0.0f;

	UPROPERTY(EditAnywhere, Category = "BoidSimParameter")
	float AlignmentAlpha;

	UPROPERTY(EditAnywhere, Category = "BoidSimParameter")
	float CohesionAlpha;
	
	UPROPERTY(EditAnywhere, Category = "BoidSimParameter")
	float SeparationAlpha;

	UPROPERTY(EditAnywhere, Category = "BoidSimParameter")
	float SeparationTime;

	UPROPERTY(EditAnywhere, Category = "BoidSimParameter")
	float CohesionAlignmentBias;

	UPROPERTY(EditAnywhere, Category = "BoidNearestNeighbourParameter")
	float Radius;

protected:
	TArray<ABoid*> BoidArray;
	TArray<FVector> DirectionVectors;
	TArray<FVector> InitialDirectionVectors;
	TArray<FVector> TargetDirectionVectors;
	
	FTransform* InstanceTransform;
	FTransform* NeighbourTransform;
	FVector AverageHeading;
	FVector AveragePosition;
	FVector SeparationHeading;
	FVector SimModeMultiplier;

	USceneComponent* SceneComponent;
	USceneComponent* RotationComponent;

	FRandomStream RandStream;
	float TimeSinceDirectionChange;
	float TimeSinceSeparationChange;
};
