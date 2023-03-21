// Fill out your copyright notice in the Description page of Project Settings.


#include "GridPawn.h"
#include "BattleshipGrid.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGridPawn::AGridPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGridPawn::BeginPlay()
{
	Super::BeginPlay();
	GameManager = GetWorld()->SpawnActor<AGameManager>(GameManagerBlueprint, FVector(0, 0, 0), FRotator::ZeroRotator);

}

// Called every frame
void AGridPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGridPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Setup Mouse Functionality
	InputComponent->BindAction(TEXT("Select"), IE_Pressed, this, &AGridPawn::OnMouseClick);

	//Setup Movement Functions
	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AGridPawn::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveRL"), this, &AGridPawn::MoveRL);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &AGridPawn::Rotate);
	PlayerInputComponent->BindAxis(TEXT("MoveUD"), this, &AGridPawn::MoveUD);

	//Bind Action is not functioning, Bind Axis used instead
	PlayerInputComponent->BindAction(TEXT("ToggleMove"), IE_Pressed, this, &AGridPawn::ToggleMove);
	PlayerInputComponent->BindAction(TEXT("RotateShipClockwise"), IE_Pressed, this, &AGridPawn::RotateShipClockwise);
	PlayerInputComponent->BindAction(TEXT("RotateShipCounterClockwise"), IE_Pressed, this, &AGridPawn::RotateShipCounterClockwise);



}

void AGridPawn::MoveFB(float Value)
{
	if (CanMove) {
		auto Location = GetActorLocation();
		Location += Value * RootComponent->GetForwardVector();
		SetActorLocation(Location);
	}
}

void AGridPawn::MoveRL(float Value)
{
	if (CanMove) {
		auto Location = GetActorLocation();
		Location += Value * RootComponent->GetRightVector();
		SetActorLocation(Location);
	}
}

void AGridPawn::Rotate(float Value)
{
	if (CanMove) {
		auto Rotation = GetActorRotation();
		Rotation.Yaw += Value * RotationSpeed;
		SetActorRotation(Rotation);
	}

}

void AGridPawn::ToggleMove()
{
	CanMove = !CanMove;
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (CanMove) {
		PC->bShowMouseCursor = false;
		PC->bEnableClickEvents = false;
		PC->bEnableMouseOverEvents = false;
	}
	else {
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
}


void AGridPawn::MoveUD(float Value)
{
	if (CanMove) {
		auto Location = GetActorLocation();
		Location += Value * RootComponent->GetUpVector();
		SetActorLocation(Location);
	}
}



//Rename to select
void AGridPawn::OnMouseClick()
{
	FHitResult HitResult;
	APlayerController* PC = Cast<APlayerController>(GetController());
	PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResult);

	if (Cast<ISelectable>(HitResult.GetActor())) {
		ISelectable* SelectedActor = Cast<ISelectable>(HitResult.GetActor());

		if (PreviouslySelectedActor != nullptr && SelectedActor != PreviouslySelectedActor) {
			PreviouslySelectedActor->Execute_Select(Cast<UObject>(PreviouslySelectedActor), false);
		}
		PreviouslySelectedActor = SelectedActor;
		SelectedActor->Execute_Select(Cast<UObject>(SelectedActor), true);

        if(GameManager->state == bGameState::PLACEMENT_STATE) {
			PlacementSelect(SelectedActor);
        }
        else if(GameManager->state == bGameState::ATTACK_STATE && Cast<AGridTile>(SelectedActor)) {
            AttackSelect(HitResult.GetActor());
        }
		

	}
}

void AGridPawn::AttackSelect(AActor* SelectedActor) {
	if (SelectedActor) {
		GameManager->SetTarget(SelectedActor);
		GameManager->FireAtTarget();
	}

}

void AGridPawn::PlacementSelect(ISelectable* SelectedActor) {
    if (Cast<AGridTile>(SelectedActor))  SelectedTile = Cast<AGridTile>(SelectedActor);
		else if (Cast<AShip>(SelectedActor)) SelectedShip = Cast<AShip>(SelectedActor);

		//Move Ship to tile if both a ship and tile are selected
		if (Cast<AGridTile>(PreviouslySelectedActor) && SelectedTile && SelectedShip) {
			TActorIterator<ABattleshipGrid> GridIterator(GetWorld(), ABattleshipGrid::StaticClass(), EActorIteratorFlags::AllActors);
			for (GridIterator; GridIterator; ++GridIterator) {
				// TODO::Check if Player Grid
				GridIterator->MoveShip(*SelectedShip, *SelectedTile);
			}
			SelectedShip = nullptr;
			SelectedTile = nullptr;
	}

}

void AGridPawn::RotateShipClockwise()
{
	if (SelectedShip != nullptr) {
		TActorIterator<ABattleshipGrid> GridIterator(GetWorld(), ABattleshipGrid::StaticClass(), EActorIteratorFlags::AllActors);
		for (GridIterator; GridIterator; ++GridIterator) {
			// TODO::Check if Player Grid
			GridIterator->RotateShip(*SelectedShip, true);
		}
	}
	
}

void AGridPawn::RotateShipCounterClockwise()
{
	if (SelectedShip != nullptr) {
		TActorIterator<ABattleshipGrid> GridIterator(GetWorld(), ABattleshipGrid::StaticClass(), EActorIteratorFlags::AllActors);
		for (GridIterator; GridIterator; ++GridIterator) {
			// TODO::Check if Player Grid
			GridIterator->RotateShip(*SelectedShip, false);
		}
	}
}

