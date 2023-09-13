// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsTrainer.h"
#include "SphereLearningAgentsTrainer.generated.h"

/**
 *
 */
UCLASS()
class SIMPLERL_API USphereLearningAgentsTrainer : public ULearningAgentsTrainer
{
	GENERATED_BODY()

public:

	void SetupRewards_Implementation() override;
	void SetRewards_Implementation(const TArray<int32>& AgentIds) override;
	void SetupCompletions_Implementation() override;
	void SetCompletions_Implementation(const TArray<int32>& AgentIds) override;
	void ResetEpisodes_Implementation(const TArray<int32>& AgentId) override;

protected:

	class UScalarVelocityReward* ScalarVelocityReward;
	class UConditionalCompletion* ConditionalCompletion;

};