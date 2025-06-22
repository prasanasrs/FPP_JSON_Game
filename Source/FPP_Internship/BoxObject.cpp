// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxObject.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/GameModeBase.h"
#include "FPP_InternshipGameMode.h"

// Sets default values
ABoxObject::ABoxObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);

}

void ABoxObject::InitBox(int32 InHealth, int32 InScore, const FString& InType, const FLinearColor& InColor)
{
    Health = InHealth;
    Score = InScore;
    Type = InType;

    if (Mesh)
    {
        UMaterialInstanceDynamic* DynMat = Mesh->CreateAndSetMaterialInstanceDynamic(0);
        if (DynMat)
        {
            DynMat->SetVectorParameterValue(TEXT("BaseColor"), InColor);
        }
    }
}

float ABoxObject::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

    Health -= static_cast<int32>(DamageAmount);

    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), GetActorRotation(), true);


    if (Health <= 0)
    {
        // Award score
        if (GetWorld())
        {
            AFPP_InternshipGameMode* GameMode = Cast<AFPP_InternshipGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
            if (GameMode)
            {
                GameMode->SetScore(Score); // Implement this in your GameMode
            }
        }

        PlayDestroyAnimation(); 
    }

    return DamageAmount;
}



// Called when the game starts or when spawned
void ABoxObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABoxObject::PlayDestroyAnimation()
{
    if (DestroyEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffect,
            GetActorLocation(), FRotator::ZeroRotator, true);
    }

    Destroy();
}
