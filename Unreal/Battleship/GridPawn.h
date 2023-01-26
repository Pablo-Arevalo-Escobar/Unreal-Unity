// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Selectable.h"
#include "GridTile.h"
#include "Ship.h"
#include "GridPawn.generated.h"

UCLASS()
class BATTLESHIP_API AGridPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGridPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	//Axis Bindings
	void MoveFB(float Value);
	void MoveRL(float Value);
	void Rotate(float Value);
	void MoveUD(float Value);

	//Action Bindings
	void ToggleMove();
	void OnMouseClick();

private:
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;

	ISelectable* PreviouslySelectedActor;
	AShip* SelectedShip;
	AGridTile* SelectedTile;

	UPROPERTY(EditAnywhere)
	bool CanMove = true;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 1.0f;
};
