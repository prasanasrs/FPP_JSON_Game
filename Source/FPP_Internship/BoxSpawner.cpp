// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxSpawner.h"
#include "BoxObject.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Engine/World.h"

// Sets default values
ABoxSpawner::ABoxSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoxSpawner::BeginPlay()
{
	Super::BeginPlay();


    FString URL = TEXT("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &ABoxSpawner::OnResponseReceived);
    Request->SetURL(URL);
    Request->SetVerb("GET");
    Request->SetHeader("Content-Type", "application/json");
    Request->ProcessRequest();
	
}

// Called every frame
void ABoxSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoxSpawner::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful || !Response.IsValid() || Response->GetResponseCode() != 200)
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP request failed"));
        return;
    }

    FString JsonString = Response->GetContentAsString();
    TSharedPtr<FJsonObject> RootObj;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

    if (!FJsonSerializer::Deserialize(Reader, RootObj) || !RootObj.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid JSON"));
        return;
    }

    TMap<FString, TSharedPtr<FJsonObject>> TypeMap;
    const TArray<TSharedPtr<FJsonValue>>* TypeArray;
    if (RootObj->TryGetArrayField("types", TypeArray))
    {
        for (const auto& Val : *TypeArray)
        {
            TSharedPtr<FJsonObject> TypeObj = Val->AsObject();
            FString TypeName = TypeObj->GetStringField("name");
            TypeMap.Add(TypeName, TypeObj);
        }
    }

    const TArray<TSharedPtr<FJsonValue>>* ObjectArray;
    if (!RootObj->TryGetArrayField("objects", ObjectArray))
        return;

    for (const auto& Val : *ObjectArray)
    {
        TSharedPtr<FJsonObject> Obj = Val->AsObject();
        FString Type = Obj->GetStringField("type");

        if (!TypeMap.Contains(Type))
            continue;

        TSharedPtr<FJsonObject> TypeDef = TypeMap[Type];
        const TArray<TSharedPtr<FJsonValue>>* ColorArr;
        FLinearColor Color = FLinearColor::White;

        if (TypeDef->TryGetArrayField("color", ColorArr) && ColorArr->Num() == 3)
        {
            Color = FLinearColor(
                (*ColorArr)[0]->AsNumber() / 255.f,
                (*ColorArr)[1]->AsNumber() / 255.f,
                (*ColorArr)[2]->AsNumber() / 255.f,
                1.0f);
        }

        int32 Health = TypeDef->GetIntegerField("health");
        int32 Score = TypeDef->GetIntegerField("score");

        FVector Location, Scale;
        FRotator Rotation;
        TSharedPtr<FJsonObject> TransformObj = Obj->GetObjectField("transform");

        auto ParseVec = [](const TArray<TSharedPtr<FJsonValue>>& Arr, FVector& OutVec)
            {
                if (Arr.Num() == 3)
                {
                    OutVec.X = Arr[0]->AsNumber();
                    OutVec.Y = Arr[1]->AsNumber();
                    OutVec.Z = Arr[2]->AsNumber();
                }
            };

        ParseVec(TransformObj->GetArrayField("location"), Location);
        ParseVec(TransformObj->GetArrayField("scale"), Scale);
        const auto& RotArr = TransformObj->GetArrayField("rotation");
        if (RotArr.Num() == 3)
        {
            Rotation = FRotator(RotArr[0]->AsNumber(), RotArr[1]->AsNumber(), RotArr[2]->AsNumber());
        }

        FActorSpawnParameters Params;
        ABoxObject* Box = GetWorld()->SpawnActor<ABoxObject>(BoxClass, Location, Rotation, Params);
        if (Box)
        {
            Box->SetActorScale3D(Scale);
            Box->InitBox(Health, Score, Type, Color);
        }
    }

}

