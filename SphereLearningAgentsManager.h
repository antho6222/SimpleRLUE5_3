// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsManager.h"
#include "LearningAgentsPolicy.h"
#include "SphereLearningAgentsTrainer.h"
#include "SphereLearningAgentsManager.generated.h"

UCLASS()
class SIMPLERL_API ASphereLearningAgentsManager : public ALearningAgentsManager
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASphereLearningAgentsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class USphereLearningAgentsInteractor* SphereLearningAgentsInteractor;

	FLearningAgentsPolicySettings LearningAgentsPolicySettings;
	ULearningAgentsPolicy* LearningAgentsPolicy;

	USphereLearningAgentsTrainer* SphereLearningAgentsTrainer;
	FLearningAgentsTrainerSettings LearningAgentsTrainerSettings;
	FLearningAgentsTrainerTrainingSettings LearningAgentsTrainerTrainingSettings;
	FLearningAgentsTrainerGameSettings LearningAgentsTrainerGameSettings;
	FLearningAgentsTrainerPathSettings LearningAgentsTrainerPathSettings;
	FLearningAgentsCriticSettings LearningAgentsCriticSettings;

	TArray<AActor*> Spheres;
	UClass* BpSphere;
	bool bTrainInProgress{ false };
	bool bTrainDone{ false };

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	bool bTrain{ true };
};
