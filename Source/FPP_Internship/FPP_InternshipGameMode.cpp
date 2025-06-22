// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPP_InternshipGameMode.h"
#include "FPP_InternshipCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPP_InternshipGameMode::AFPP_InternshipGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;



}

void AFPP_InternshipGameMode::SetScore(int32 NewScore)
{
	Score +=  NewScore;
	UE_LOG(LogTemp, Log, TEXT("Score: %d"), Score);
}

int32 AFPP_InternshipGameMode::GetScore() const
{
	return Score;
}
