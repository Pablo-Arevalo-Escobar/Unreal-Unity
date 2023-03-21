// Fill out your copyright notice in the Description page of Project Settings.


#include "Boid.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
ABoid::ABoid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoidMesh"));
	StaticMesh->SetupAttachment(SceneComponent);
}


// Called when the game starts or when spawned
void ABoid::BeginPlay()
{
	Super::BeginPlay();
	Speed = 100.0f;
	BiasTime = 5.0f;
	TimeSinceDirChange = 0.0f;
	DirectionVector = FMath::VRand();
	NoiseScale = 1.0f;
	RandStream.GenerateNewSeed();
}


// Called every frame
void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TimeSinceDirChange <= 0.0f) {
		InitialDirectionVector = DirectionVector;
		FVector RandomDir =	RandomDirection();
		DirectionTargetVector = RandomWalk();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("X %f Y %f Z %f"), RandomDir.X, RandomDir.Y, RandomDir.Z));

	}
	else if (TimeSinceDirChange > BiasTime) { TimeSinceDirChange = 0.0f; return; }
	else {
		
		double Alpha = TimeSinceDirChange/BiasTime;
		DirectionVector = FMath::Lerp(InitialDirectionVector, DirectionTargetVector, Alpha);
		DirectionVector.Normalize();
	}

	
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FVector(0,0,0), DirectionVector);
	SetActorRelativeRotation(Rotation);
	TimeIntegration(DeltaTime);
}

void ABoid::TimeIntegration(float DeltaTime)
{
	TimeSinceDirChange += DeltaTime;
	FVector NewLocation = GetActorLocation() + DeltaTime * Speed * DirectionVector;
	SetActorLocation(NewLocation);
	// V= V + a*t
	// S = S + v*t
}

FVector ABoid::RandomDirection()
{
	RandStream.GenerateNewSeed();
	return 	RandStream.GetUnitVector();
}


FVector ABoid::RandomWalk()
{
	/*FVector RandomDirection = DirectionVector;
	FVector DirectionNoise = FMath::VRand() * NoiseScale;
	RandomDirection += DirectionNoise;
	RandomDirection.Normalize();*/
	float realtimeSeconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	FMath::RandInit((int)realtimeSeconds);
	return FMath::VRand() * NoiseScale;
}

void ABoid::SetNoiseScale(float scale)
{
	NoiseScale = scale;
}

FVector ABoid::GetVelocity()
{
	return FVector();
}

void ABoid::SetVelocity(FVector BoidVelocity)
{
	DirectionVector = BoidVelocity;
}




