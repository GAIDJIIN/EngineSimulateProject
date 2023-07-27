#include "Core/EngineComponent.h"
// Fill out your copyright notice in the Description page of Project Settings.

#include "TimerManager.h"
#include "Core/EngineComponent.h"

#include "Core/EngineDataAsset.h"

UEngineComponent::UEngineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UEngineComponent::GetIsEngineWork() const
{
	if(!GetWorld()) return false;
	return GetWorld()->GetTimerManager().IsTimerActive(EngineWorkTimerHandle);
}

float UEngineComponent::GetPercentToOverheat() const
{
	if(!EngineInputData) return -1.f;
	const float LocalPercent = EngineTemperature != 0.f ? EngineTemperature/EngineInputData->T_overheat : 0;
	return LocalPercent < 1.f ? LocalPercent : 1.f; 
}

void UEngineComponent::BeginPlay()
{
	Super::BeginPlay();
	check(EngineInputData)
	
}

void UEngineComponent::StartEngine()
{
	if (!GetWorld() || GetIsEngineWork()) return;
	EngineTemperature = AmbientTemperature;
	TimeToOverheating = 0;
	DeltaTemp = 0.f;
	InitializeProperties();
	GetWorld()->GetTimerManager().SetTimer(EngineWorkTimerHandle, this, &UEngineComponent::EngineWork, EngineWorkTimePeriod, true);
	OnStartEngine.Broadcast();
}

void UEngineComponent::StopEngine()
{
	if(!GetWorld() || !GetIsEngineWork()) return;
	GetWorld()->GetTimerManager().ClearTimer(EngineWorkTimerHandle);
	OnStopEngine.Broadcast();
}

void UEngineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UEngineComponent::EngineWork()
{
	if (ConditionToStopEngineWork() || !EngineInputData) {
		OnOverheatEngine.Broadcast();
		StopEngine();
		return;
	}
	EngineWorkLogic();
}

void UEngineComponent::EngineWorkLogic()
{
}

void UEngineComponent::InitializeProperties()
{
}

float UEngineComponent::CalculateCoolingSpeed()
{
	return 0.f;
}

float UEngineComponent::CalculateOverheatSpeed()
{
	return 0.f;
}
