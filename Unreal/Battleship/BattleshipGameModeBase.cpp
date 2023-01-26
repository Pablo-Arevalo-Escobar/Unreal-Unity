// Copyright Epic Games, Inc. All Rights Reserved.


#include "BattleshipGameModeBase.h"

void ABattleshipGameModeBase::InitGameState()
{
    Super::InitGameState();

    //Set default pawn
    if (DefaultPawnClass == ADefaultPawn::StaticClass() || !DefaultPawnClass) {
        DefaultPawnClass = CustomGridPawnClass;
    };
}
