// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

UCLASS()
class BOIDS_API ABoid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoid();

	FVector RandomWalk();
	void SetNoiseScale(float scale);

	FVector GetVelocity();
	void SetVelocity(FVector BoidVelocity);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void TimeIntegration(float DeltaTime);
	FVector RandomDirection();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	FVector DirectionVector;
	float NoiseScale;

	UPROPERTY(EditAnywhere, Category = "BoidParameter")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoidSimParameter")
	float BiasTime;

	UPROPERTY(EditAnywhere, Category = "BoidSimParameter")
	float Speed;

private:
	FRandomStream RandStream;
	USceneComponent* SceneComponent;
	FVector InitialDirectionVector;
	FVector DirectionTargetVector;

	float TimeSinceDirChange;


	
};
