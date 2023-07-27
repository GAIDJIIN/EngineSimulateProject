// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/DVSEngineComponent.h"
#include "Core/EngineDVSDataAsset.h"

float UDVSEngineComponent::CalculateOverheatSpeed()
{
	TObjectPtr<UEngineDVSDataAsset> LocalEngineData = Cast<UEngineDVSDataAsset>(GetEngineInputData());
	if (!LocalEngineData) return 0.f;
	return CurrentM * LocalEngineData->H_M + CurrentV*CurrentV*LocalEngineData->H_V;
}

float UDVSEngineComponent::CalculateCoolingSpeed()
{
	TObjectPtr<UEngineDVSDataAsset> LocalEngineData = Cast<UEngineDVSDataAsset>(GetEngineInputData());
	if (!LocalEngineData) return 0.f;
	return LocalEngineData->C * (GetAmbientTemperature() - GetEngineTemperature());
}


void UDVSEngineComponent::EngineWorkLogic()
{
	TObjectPtr<UEngineDVSDataAsset> LocalEngineData = Cast<UEngineDVSDataAsset>(GetEngineInputData());
	if (!LocalEngineData) {
		StopEngine();
		return;
	}
	SetTimeToOverheating(GetTimeToOverheating()+1);
	CurrentV += Acceleration;
	if (NumberOfMandV < LocalEngineData->M.Num() - 2)
		NumberOfMandV += CurrentV < LocalEngineData->V[NumberOfMandV + 1] ? 0 : 1;
	double up = (CurrentV - LocalEngineData->V[NumberOfMandV]);
	double down = (LocalEngineData->V[NumberOfMandV + 1] - LocalEngineData->V[NumberOfMandV]);
	double factor = (LocalEngineData->M[NumberOfMandV + 1] - LocalEngineData->M[NumberOfMandV]);
	CurrentM = up / down * factor + LocalEngineData->M[NumberOfMandV];
	SetEngineTemperature(GetEngineTemperature() + CalculateCoolingSpeed() + CalculateOverheatSpeed());
	Acceleration = CurrentM * LocalEngineData->I; // Acceleration
	SetDeltaTemp(LocalEngineData->T_overheat - GetEngineTemperature()); // Temperature Delta
}

void UDVSEngineComponent::InitializeProperties()
{ 
	TObjectPtr<UEngineDVSDataAsset> LocalEngineData = Cast<UEngineDVSDataAsset>(GetEngineInputData());
	if (!LocalEngineData) return;
	SetTimeToOverheating(0);
	CurrentM = LocalEngineData->M[0];
	CurrentV = LocalEngineData->V[0];
	NumberOfMandV = 0;
	Acceleration = CurrentM * LocalEngineData->I; // Acceleration
	SetDeltaTemp(LocalEngineData->T_overheat - GetEngineTemperature()); // Temperature Delta
}
