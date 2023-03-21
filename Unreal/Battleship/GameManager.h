// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Battleship/BattleshipGrid.h>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Battleship/ProjectileLauncher.h>
#include "GameManager.generated.h"

UENUM()
enum class bGameState : uint8
{
	INVALID,
	PLACEMENT_STATE,
	ATTACK_STATE,
	MAX UMETA(Hidden)
}; 
/**
 * The Game Manager:
 *  Responsible for initalizing the battleship grids and handling the turn based nature of the game
 *  Stores two battleship grid and a turn indicator 
 * */

UCLASS()
class BATTLESHIP_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();
    void run();

	void SetTarget(AActor* NewTarget);
	
	UFUNCTION(BlueprintCallable)
		AActor* GetTarget();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void FireAtTarget();
	virtual void FireAtTarget_Implementation() ;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    UPROPERTY(EditAnywhere)
    bGameState state = bGameState::PLACEMENT_STATE;

protected:
	AActor* target;

    UPROPERTY(EditAnywhere)
    TSubclassOf<ABattleshipGrid> gridBlueprint;

    UPROPERTY(EditAnywhere)
    ABattleshipGrid* player1Grid;

    UPROPERTY(EditAnywhere)
    ABattleshipGrid* player2Grid;

    UPROPERTY(EditAnywhere)
    AProjectileLauncher* projectileLauncher;
};
