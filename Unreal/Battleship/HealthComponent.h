// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathTriggerSignature);
/*
* Health component is used to trigger an explosion whenver a projectile enters its vicinity
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLESHIP_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();


	UFUNCTION(BlueprintCallable)
		void TakeDamage(int damageCount);

	UFUNCTION(BlueprintCallable)
		void AddHealth(int healthAdded);

	UFUNCTION(BlueprintCallable)
		int GetHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FOnDeathTriggerSignature OnDeathTrigger;
protected:
	UPROPERTY(EditAnywhere)
	int Health = 100;

	

		
};
