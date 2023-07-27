// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EngineDataAsset.generated.h"

UCLASS(Abstract)
class DVSENGINE_API UEngineDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "DVS Input Data", meta = (ClampMin = "0.0"))
		float T_overheat = 110.f; // Overheating Temperature
};
