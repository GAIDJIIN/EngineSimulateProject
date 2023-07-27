// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EngineComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartEngine);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopEngine);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverheatEngine);

class UEngineDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract )
class DVSENGINE_API UEngineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEngineComponent();

	UFUNCTION(BlueprintCallable)
		void BP_StartEngine() { StartEngine(); }
	UFUNCTION(BlueprintCallable)
		void BP_StopEngine() { StopEngine(); }
	
	// Getter
	UFUNCTION(BlueprintCallable)
		float GetAmbientTemperature() const { return AmbientTemperature; }
	UFUNCTION(BlueprintCallable)
		float GetEngineTemperature() const { return EngineTemperature; }
	UFUNCTION(BlueprintCallable)
		int32 GetTimeToOverheating() const { return TimeToOverheating; }
	UFUNCTION(BlueprintCallable)
		bool GetIsEngineWork() const;
	UFUNCTION(BlueprintCallable)
		float GetPercentToOverheat() const;
	UEngineDataAsset* GetEngineInputData() const { return EngineInputData; }
	float GetDeltaTemp() const { return DeltaTemp; }
	
	// Setter
	void SetTimeToOverheating(const int32 NewTimeToOverheating) { TimeToOverheating = NewTimeToOverheating; }
	void SetDeltaTemp(const float NewDeltaTemp) { DeltaTemp = NewDeltaTemp; }
	void SetEngineTemperature(const float NewEngineTemperature) { EngineTemperature = NewEngineTemperature; }

	// Delegate
	UPROPERTY(BlueprintAssignable)
		FOnStartEngine OnStartEngine;
	UPROPERTY(BlueprintAssignable)
		FOnStopEngine OnStopEngine;
	UPROPERTY(BlueprintAssignable)
		FOnOverheatEngine OnOverheatEngine;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Engine Main Logic
	void StartEngine();
	void StopEngine();
	void EngineWork();
	virtual bool ConditionToStopEngineWork() const { return DeltaTemp <= 0.f; }
	virtual void EngineWorkLogic();
	virtual void InitializeProperties(); // Initialize properties before start engine
	// Calculate Speed
	virtual float CalculateCoolingSpeed();
	virtual float CalculateOverheatSpeed();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	// Blueprint
	UPROPERTY(EditAnywhere, Category = "Engine Data", meta = (bAllowPrivateAccess))
		TObjectPtr<UEngineDataAsset> EngineInputData = nullptr;
	UPROPERTY(EditAnywhere, Category = "Engine Data", meta = (bAllowPrivateAccess, ClampMin="0.00001"))
		float EngineWorkTimePeriod = 1.f;
	UPROPERTY(EditAnywhere, Category = "Engine Data", meta = (bAllowPrivateAccess))
		float AmbientTemperature = 1.f;
	FTimerHandle EngineWorkTimerHandle;
	// CPP
	float EngineTemperature = 0.f;
	int32 TimeToOverheating = 0;
	float DeltaTemp = 0.f;
};
