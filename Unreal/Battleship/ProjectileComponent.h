// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLESHIP_API UProjectileComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectileComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//TODO:: IMPLEMENT A ON PROJECTILE LAUNCH EVENT WHICH CAN BE USED TO TRIGGER THE PARTICLE EFFECTS
protected:
	UPROPERTY(EditAnywhere)
	AActor* Target;

	UPROPERTY(EditAnywhere)
		float ArcHeightMultiplier = 2.0f;

	UPROPERTY(EditAnywhere)
	float MinArcHeight = 500.0f;

	UPROPERTY(EditAnywhere)
	float Gravity = -1.0f;

	UPROPERTY(EditAnywhere)
	float Speed = 1.0f;

private:
	FVector Velocity;
	FVector Acceleration;

	bool ProjectileLaunched = false;
	float TimeElapsed = 0;
	float TimeTaken;
	float HorizontalSpeed;
};
