// Fill out your copyright notice in the Description page of Project Settings.
#include "SphereLearningAgentsInteractor.h"
#include "LearningAgentsObservations.h"
#include "LearningAgentsActions.h"
#include "LearningAgentsManager.h"
#include "SpherePawn.h"

void USphereLearningAgentsInteractor::SetupObservations_Implementation()
{
    Super::SetupObservations_Implementation();
    VelocityObservation = UVelocityObservation::AddVelocityObservation(this, "Velocity", 100.0f);
}

void USphereLearningAgentsInteractor::SetObservations_Implementation(const TArray<int32>& AgentIds)
{
    Super::SetObservations_Implementation(AgentIds);

    if (VelocityObservation != nullptr) {
        for (const int32& AgentId : AgentIds) {
            const auto& Agent = GetAgentManager()->GetAgent(AgentId);
            if (ASpherePawn* SpherePawn = Cast<ASpherePawn>(Agent)) {
                VelocityObservation->SetVelocityObservation(AgentId, SpherePawn->GetSphereVelocity());
            }
        }
    }
}

void USphereLearningAgentsInteractor::SetupActions_Implementation()
{
    Super::SetupActions_Implementation();
    MoveXAction = UFloatAction::AddFloatAction(this, "MoveX", 10000.0f);
    MoveYAction = UFloatAction::AddFloatAction(this, "MoveY", 10000.0f);
}

void USphereLearningAgentsInteractor::GetActions_Implementation(const TArray<int32>& AgentIds)
{
    Super::GetActions_Implementation(AgentIds);

    if (MoveXAction != nullptr && MoveYAction != nullptr) {
        for (const int32& AgentId : AgentIds) {
            float MoveXActionValue = MoveXAction->GetFloatAction(AgentId);
            float MoveYActionValue = MoveYAction->GetFloatAction(AgentId);
            const auto& Agent = GetAgentManager()->GetAgent(AgentId);
            if (ASpherePawn* SpherePawn = Cast<ASpherePawn>(Agent)) {
                SpherePawn->MoveX(MoveXActionValue);
                SpherePawn->MoveY(MoveYActionValue);
            }
        }
    }
}
