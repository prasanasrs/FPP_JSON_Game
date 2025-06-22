// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxSpawner.generated.h"


UCLASS()
class FPP_INTERNSHIP_API ABoxSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABoxObject> BoxClass;

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};
