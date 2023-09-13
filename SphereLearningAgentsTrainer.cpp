// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereLearningAgentsTrainer.h"
#include "LearningAgentsRewards.h"
#include "LearningAgentsCompletions.h"
#include "LearningAgentsManager.h"
#include "SpherePawn.h"

void USphereLearningAgentsTrainer::SetupRewards_Implementation()
{
    Super::SetupRewards_Implementation();

    ScalarVelocityReward = UScalarVelocityReward::AddScalarVelocityReward(this, "Velocity", 1.0f, 100.0f);
}

void USphereLearningAgentsTrainer::SetRewards_Implementation(const TArray<int32>& AgentIds)
{
    Super::SetRewards_Implementation(AgentIds);

    if (ScalarVelocityReward != nullptr) {
        for (const int32& AgentId : AgentIds) {
            const auto& Agent = GetAgentManager()->GetAgent(AgentId);
            if (ASpherePawn* SpherePawn = Cast<ASpherePawn>(Agent)) {
                const FVector TargetSpeed = FVector(-100.0f, 0.0f, 0.0f);
                // Reward is to roll at the target speed
                float Reward = 100.0f - ((SpherePawn->GetSphereVelocity() - TargetSpeed).Size());
                ScalarVelocityReward->SetScalarVelocityReward(AgentId, Reward);
            }
        }
    }
}

void USphereLearningAgentsTrainer::SetupCompletions_Implementation()
{
    Super::SetupCompletions_Implementation();
    ConditionalCompletion = UConditionalCompletion::AddConditionalCompletion(this, "Completion", ELearningAgentsCompletion::Termination);
}

void USphereLearningAgentsTrainer::SetCompletions_Implementation(const TArray<int32>& AgentIds)
{
    Super::SetCompletions_Implementation(AgentIds);
    if (ConditionalCompletion != nullptr) {
        for (const int32& AgentId : AgentIds) {
            // I do not use completion, but we can use it (eg. if a driving car getting off the road)
            ConditionalCompletion->SetConditionalCompletion(AgentId, false);
        }
    }
}

void USphereLearningAgentsTrainer::ResetEpisodes_Implementation(const TArray<int32>& AgentIds)
{
    Super::ResetEpisodes_Implementation(AgentIds);

    for (const int32& AgentId : AgentIds) {
        const auto& Agent = GetAgentManager()->GetAgent(AgentId);
        if (ASpherePawn* SpherePawn = Cast<ASpherePawn>(Agent)) {
            SpherePawn->ResetPosition();
        }
    }
}
