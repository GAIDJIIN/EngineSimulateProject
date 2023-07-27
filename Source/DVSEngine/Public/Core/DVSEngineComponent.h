// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/EngineComponent.h"
#include "DVSEngineComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DVSENGINE_API UDVSEngineComponent : public UEngineComponent
{
	GENERATED_BODY()
private:
	int32 CurrentM;
	int32 CurrentV;
	float Acceleration = 0.f;
	int32 NumberOfMandV = 0;
protected:
	virtual void EngineWorkLogic() override;
	virtual void InitializeProperties() override;
	virtual float CalculateCoolingSpeed() override;
	virtual float CalculateOverheatSpeed() override;
};
