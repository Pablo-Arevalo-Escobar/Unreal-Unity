// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Selectable.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"
#include "GameFramework/DefaultPawn.h"

#include "Ship.generated.h"

UENUM()
enum class EShipType :uint8
{
	ONE_TILE,
	TWO_TILE,
	THREE_TILE,
	MAX UMETA(Hidden)
};

UCLASS()
class BATTLESHIP_API AShip : public AActor, public ISelectable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShip();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Select(bool IsSelected);
	virtual void Select_Implementation(bool Value) override;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EShipType ShipType;

private:
	UPROPERTY(BlueprintAssignable)
	FOnSelectedTriggerSignature OnSelectedTrigger;


protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		UHealthComponent* Health;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* TriggerClass = ADefaultPawn::StaticClass();
	//UPROPERTY(EditAnywhere, Category = "ModuleType")
	//TSubclassOf<AShipModule> CoreModule;

	//UPROPERTY(EditAnywhere, Category = "ModuleType")
	//TSubclassOf<AShipModule> ExternalModule;

	//UPROPERTY(EditAnywhere, Category = "ModuleType")
	//TSubclassOf<AShipModule> InternalModule;

	//UPROPERTY(EditInstanceOnly)
	//TArray<AShipModule*> ShipModules;
};
