// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileLauncher.h"

// Sets default values
AProjectileLauncher::AProjectileLauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	LauncherMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LauncherMesh"));
	ProjectileComponent = CreateDefaultSubobject<UProjectileComponent>(TEXT("ProjectileComponent"));

	LauncherMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetupAttachment(ProjectileComponent);


}

// Called when the game starts or when spawned
void AProjectileLauncher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AProjectileLauncher::LaunchProjectile(AActor* Target)
{
	ProjectileComponent->SetTarget(Target);
	ProjectileComponent->Launch();
}

