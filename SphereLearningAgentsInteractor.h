// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsInteractor.h"
#include "SphereLearningAgentsInteractor.generated.h"

/**
 *
 */
UCLASS()
class SIMPLERL_API USphereLearningAgentsInteractor : public ULearningAgentsInteractor
{
	GENERATED_BODY()

public:

	void SetupObservations_Implementation() override;
	void SetObservations_Implementation(const TArray<int32>& AgentIds) override;
	void SetupActions_Implementation() override;
	void GetActions_Implementation(const TArray<int32>& AgentIds) override;

protected:

	class UVelocityObservation* VelocityObservation;
	class UFloatAction* MoveXAction;
	class UFloatAction* MoveYAction;

};
