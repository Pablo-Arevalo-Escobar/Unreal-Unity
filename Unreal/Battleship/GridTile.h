// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Selectable.h"
#include "GridTile.generated.h"

UENUM()
enum class ETileType : uint8
{
	INVALID,
	GRASS,
	WATER,
	MAX UMETA(Hidden)
};




UCLASS()
class BATTLESHIP_API AGridTile : public AActor, public ISelectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridTile();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Select(bool IsSelected); 
	virtual void Select_Implementation(bool Value) override;

protected:
	UFUNCTION()
	void OnClicked(AActor* TouchedActor, FKey ButtonPressed);

public:
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleInstanceOnly)
	FIntPoint TileIndex;

private:
	UPROPERTY(BlueprintAssignable)
	FOnSelectedTriggerSignature OnSelectedTrigger;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ETileType TileType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* TileMesh;



};
