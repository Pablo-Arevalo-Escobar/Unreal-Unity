// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileComponent.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values for this component's properties
UProjectileComponent::UProjectileComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UProjectileComponent::SetTarget(AActor* NewTarget) {
	this->Target = NewTarget;
}

void UProjectileComponent::Launch() {
	if(Target== nullptr) {
		return;
	}
	FVector TargetDisplacement = Target->GetActorLocation() - GetRelativeLocation();
	FVector HorizontalDisplacement = TargetDisplacement - (0.15 * TargetDisplacement);
	HorizontalDisplacement.Z = 0;

	float ArcHeight = TargetDisplacement.Z * ArcHeightMultiplier;
	float offset = 1.18f;
	if (TargetDisplacement.Z < 0) {
		ArcHeight = MinArcHeight;
		offset = 1.0f;
	}



	float VerticalSpeed = FMath::Sqrt(ArcHeight * 2 * FMath::Abs(Gravity));
	TimeTaken = (2 * VerticalSpeed) / FMath::Abs(Gravity);
	HorizontalSpeed = (HorizontalDisplacement.Length() * offset) / TimeTaken;

	HorizontalDisplacement.Normalize();
	Velocity = FVector(HorizontalDisplacement.X * HorizontalSpeed, HorizontalDisplacement.Y * HorizontalSpeed, VerticalSpeed);
	Acceleration = FVector(0.0, 0.0, Gravity);

	ProjectileLaunched = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("My TimeTaken is: %f"), TimeTaken));

}


// Called when the game starts
void UProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
	if (Gravity == 0) { Gravity = 1; }
	if (Target != nullptr) {
		Launch();
	}
}


// Called every frame
void UProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (ProjectileLaunched) {
		float TimeStep = DeltaTime * Speed;
		TimeElapsed += TimeStep;
		Velocity = Velocity + (Acceleration * TimeStep);
		FVector NewPosition = GetRelativeLocation() + (Velocity * TimeStep);

		if (TimeElapsed > TimeTaken)
			ProjectileLaunched = false;

		//Set Rotation
		FVector VelocityDirection = Velocity;
		VelocityDirection.Normalize();
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FVector(0, 0, 0), VelocityDirection);
		//Rotation *= 2;
		SetRelativeRotation(Rotation);
		SetRelativeLocation(NewPosition);
	}

	
}

AActor* UProjectileComponent::GetTarget()
{
	return Target;
}

