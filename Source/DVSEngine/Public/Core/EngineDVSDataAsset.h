// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/EngineDataAsset.h"
#include "EngineDVSDataAsset.generated.h"

UCLASS()
class DVSENGINE_API UEngineDVSDataAsset : public UEngineDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "DVS Input Data")
		float I = 0.1f; // Inertion Moment
	UPROPERTY(EditAnywhere, Category = "DVS Input Data")
		float H_M = 0.01f; // Overheat Speed - Rotating Moment
	UPROPERTY(EditAnywhere, Category = "DVS Input Data")
		float H_V = 0.0001f; // Overheat Speed - Rotate Kalenval Speed
	UPROPERTY(EditAnywhere, Category = "DVS Input Data")
		float C = 0.1f; // Cooling Speed - Temperature
	UPROPERTY(EditAnywhere, Category = "DVS Input Data")
		TArray<int32> M = { 20,75,100,105,75,0 }; // Rotating Moment
	UPROPERTY(EditAnywhere, Category = "DVS Input Data")
		TArray<int32> V = { 0,75,150,200,250,300 }; // Rotation Speed
};
