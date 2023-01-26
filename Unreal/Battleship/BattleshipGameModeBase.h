// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/DefaultPawn.h"
#include "GridPawn.h"
#include "BattleshipGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESHIP_API ABattleshipGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void InitGameState() override;

private:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<AGridPawn> CustomGridPawnClass = AGridPawn::StaticClass();

};
