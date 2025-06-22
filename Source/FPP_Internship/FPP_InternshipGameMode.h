// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPP_InternshipGameMode.generated.h"

UCLASS(minimalapi)
class AFPP_InternshipGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPP_InternshipGameMode();

	UFUNCTION(BlueprintCallable, Category = "CustomFunctions")
	void SetScore(int32 NewScore);

	UFUNCTION(BlueprintCallable, Category = "CustomFunctions")
	int32 GetScore() const;

private:
	int32 Score = 0;
};



