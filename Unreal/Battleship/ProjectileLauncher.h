// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Battleship/ProjectileComponent.h>
#include "ProjectileLauncher.generated.h"

UCLASS()
class BATTLESHIP_API AProjectileLauncher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileLauncher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void LaunchProjectile(AActor* Target);

protected:

	TSubclassOf<AActor> ProjectileBlueprint;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LauncherMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProjectileComponent* ProjectileComponent;

};
