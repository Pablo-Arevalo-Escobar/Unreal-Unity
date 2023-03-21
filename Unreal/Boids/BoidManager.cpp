// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidManager.h"
#include <string>
#include <Boids/Boid.h>
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values
ABoidManager::ABoidManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = SceneComponent;
	InstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Static"));
	InstancedMesh->SetupAttachment(SceneComponent);
}

ABoidManager::~ABoidManager()
{
	delete InstanceTransform;
	delete NeighbourTransform;
}

// Called when the game starts or when spawned
void ABoidManager::BeginPlay()
{
	Super::BeginPlay();
	RandStream.GenerateNewSeed();
	//Initialize Arrays
	DirectionVectors.SetNumZeroed(NumberOfBoids);
	InitialDirectionVectors.SetNumZeroed(NumberOfBoids);
	TargetDirectionVectors.SetNumZeroed(NumberOfBoids);
	BoidArray.SetNumZeroed(NumberOfBoids);

	InstanceTransform = new FTransform();
	NeighbourTransform = new FTransform();

	SeparationHeading = FVector::OneVector;
	TimeSinceSeparationChange = 0.0f;
	NoiseScale = 1;
	
	if (SimMode == ESimMode::_2D) 
		SimModeMultiplier = FVector(1.0, 1.0, 0.0);
	else 
		SimModeMultiplier = FVector(1.0, 1.0, 1.0);

	for (int32 i = 0; i < NumberOfBoids; ++i) {
		FVector SpawnLocation = FMath::VRand()*RandStream.FRandRange(1,GroupRadius) * SimModeMultiplier;
		FTransform transform(FRotator(0.0, -90.0, 0.0),SpawnLocation, FVector::OneVector*Scale);

		InstancedMesh->AddInstance(transform);
		FVector DirVector(RandStream.GetUnitVector());
		FVector RandVec = FMath::VRand() * SimModeMultiplier;
		DirectionVectors.Add(RandVec);
	}
}


//Boid Behaviour Algorithm
	/*
	*	(1) Alignment:
	*			Steer towards the average heading of local flockmates
	*			During the for loop add all of the velocity vectors to the AverageVelocity Variable and then divide this value by the number of
	*			boids. Then linearly interpolate between the new direction vector and the average velocity using a AlignmentAlpha variable
	*	(2) Separation:
	*			Steer to avoid local flockmates
	*	(3) Cohesion:
	*			Steer to move towards the average position (center of mass) of local flockmates
	*
	*	TODO:
	*		* Nearest neighbour implementation
	*		* Obstacle avoidance
	*
	*/
void ABoidManager::Tick(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Manager Location %f %f %f"),AveragePosition.X, AveragePosition.Y, AveragePosition.Z));
	Super::Tick(DeltaTime);
	RandStream.GenerateNewSeed();

	if (TimeSinceDirectionChange > BiasTime) 
		TimeSinceDirectionChange = 0.0f;
	

	AlignmentAndCohesion();
	for (int i = 0; i < NumberOfBoids; ++i) {
		RandomWalk(i);
		TimeIntegration(i,DeltaTime);
	}

	if (TimeSinceSeparationChange >= SeparationTime)
		TimeSinceSeparationChange = 0.0f;

	TimeSinceSeparationChange += DeltaTime;
	TimeSinceDirectionChange += DeltaTime;
	InstancedMesh->MarkRenderStateDirty();	
}

void ABoidManager::AlignmentAndCohesion() {
	AveragePosition = FVector::ZeroVector;
	AverageHeading = FVector::ZeroVector;
	for (int i = 0; i < NumberOfBoids; ++i) {
		AverageHeading += DirectionVectors[i];
		InstancedMesh->GetInstanceTransform(i, *InstanceTransform);
		AveragePosition += InstanceTransform->GetLocation();
	}
	AverageHeading /= NumberOfBoids;
	AveragePosition /= NumberOfBoids;
}

void ABoidManager::RandomWalk(int i)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("BiasTime %f, CurrTime %f"), BiasTime, TimeSinceDirectionChange));
	if (TimeSinceDirectionChange <= 0.0f) {
		InitialDirectionVectors[i] = DirectionVectors[i];
		TargetDirectionVectors[i] = FMath::VRand() * SimModeMultiplier;
	}
	if (TimeSinceSeparationChange >= SeparationTime) {
		Separation(i);
	}
	else {
		InstancedMesh->GetInstanceTransform(i, *InstanceTransform);

		FVector AlignedTargetDirection = FMath::Lerp(TargetDirectionVectors[i], AverageHeading, AlignmentAlpha);
		FVector AveragePositionDirection = AveragePosition - InstanceTransform->GetLocation();
		AveragePositionDirection.Normalize();
		FVector CohesionTargetDirection = FMath::Lerp(TargetDirectionVectors[i], AveragePositionDirection, CohesionAlpha);
		FVector AlignmentCohesionDirection = FMath::Lerp(AlignedTargetDirection, CohesionTargetDirection, CohesionAlignmentBias);
		FVector FinalTargetDirection = FMath::Lerp(AlignmentCohesionDirection, SeparationHeading, SeparationAlpha);

		float Alpha = TimeSinceDirectionChange / BiasTime;
		DirectionVectors[i] = FMath::Lerp(InitialDirectionVectors[i], FinalTargetDirection, Alpha);
		DirectionVectors[i].Normalize();
	}
}

void ABoidManager::Separation(int Index)
{
	InstancedMesh->GetInstanceTransform(Index, *InstanceTransform);
	SeparationHeading = FVector::ZeroVector;
	int NumberFound = 0;
	for (int i = 0; i < NumberOfBoids; ++i) {
		if (i == Index) continue;
		InstancedMesh->GetInstanceTransform(i, *NeighbourTransform);

		if (FVector::Distance(InstanceTransform->GetLocation(), NeighbourTransform->GetLocation()) < Radius) {
			SeparationHeading += (NeighbourTransform->GetLocation() - InstanceTransform->GetLocation());
			++NumberFound;
		}
	}
	if (SeparationHeading == FVector::ZeroVector) return;
	SeparationHeading /= NumberFound;
	SeparationHeading *= -1;
}


void ABoidManager::TimeIntegration(int i, float DeltaTime)
{
	InstancedMesh->GetInstanceTransform(i, *InstanceTransform);
	if (InstanceTransform == nullptr) { return; }

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("DeltaTime %f Speed %f, Direction %f %f %f"), DeltaTime,Speed,DirectionVectors[i].X, DirectionVectors[i].Y, DirectionVectors[i].Z));
	FVector NewLocation = InstanceTransform->GetLocation() + DeltaTime * Speed * DirectionVectors[i];
	InstanceTransform->SetLocation(NewLocation);
	FRotator InitialRotation = FRotator(0, -90.0f, 0.0f);
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FVector(0, 0, 0), DirectionVectors[i]);
	FTransform NewTransform = FTransform(FRotator(Rotation.Pitch - 90.0, Rotation.Yaw, Rotation.Roll), NewLocation, FVector::OneVector * Scale);
	InstancedMesh->UpdateInstanceTransform(i, NewTransform, false, false, false);
}
