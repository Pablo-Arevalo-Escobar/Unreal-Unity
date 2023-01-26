// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorTest.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTestComponentSignature, bool, IsTopEndpoint);


UCLASS()
class BATTLESHIP_API AMyActorTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActorTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnTestComponentSignature OnTestComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
