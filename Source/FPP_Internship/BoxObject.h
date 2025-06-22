// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxObject.generated.h"

class UParticleSystem;
class UAnimSequence;

UCLASS()
class FPP_INTERNSHIP_API ABoxObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxObject();

	void InitBox(int32 InHealth, int32 InScore, const FString& InType, const FLinearColor& InColor);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlayDestroyAnimation();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* HitEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* DestroyEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Score")
	int32 Score;


	int32 Health;
	FString Type;

};
