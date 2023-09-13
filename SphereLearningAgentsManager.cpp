// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereLearningAgentsManager.h"
#include "SphereLearningAgentsInteractor.h"
#include "Kismet/GameplayStatics.h"
#include "SpherePawn.h"

// Sets default values
ASphereLearningAgentsManager::ASphereLearningAgentsManager()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UClass> Asset(TEXT("Blueprint'/Game/Blueprints/BpSpherePawn.BpSpherePawn_C'"));
    BpSphere = Asset.Object;
}

// Called when the game starts or when spawned
void ASphereLearningAgentsManager::BeginPlay()
{
    Super::BeginPlay();

    if (BpSphere != nullptr)
    {
        const auto Location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
        for (int32 i = 0; i < 31; ++i) {
            GetWorld()->SpawnActor<ASpherePawn>(BpSphere, Location, FRotator(0, 0, 0));
        }
    }

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpherePawn::StaticClass(), Spheres);

    for (const auto& Sphere : Spheres) {
        AddAgent(Sphere);
    }

    const auto& Components = GetComponents();
    for (const auto& Component : Components) {
        if (USphereLearningAgentsInteractor* LearningAgentsInteractor = Cast<USphereLearningAgentsInteractor>(Component)) {
            SphereLearningAgentsInteractor = LearningAgentsInteractor;
        }
        else if (USphereLearningAgentsTrainer* LearningAgentsTrainer = Cast<USphereLearningAgentsTrainer>(Component)) {
            SphereLearningAgentsTrainer = LearningAgentsTrainer;
        }
        else if (ULearningAgentsPolicy* LearningAgentsPlcy = Cast<ULearningAgentsPolicy>(Component)) {
            LearningAgentsPolicy = LearningAgentsPlcy;
        }
    }

    if (SphereLearningAgentsInteractor != nullptr && SphereLearningAgentsTrainer != nullptr && LearningAgentsPolicy != nullptr) {
        SphereLearningAgentsInteractor->SetupInteractor();
        LearningAgentsPolicy->SetupPolicy(SphereLearningAgentsInteractor, LearningAgentsPolicySettings);
        SphereLearningAgentsTrainer->SetupTrainer(SphereLearningAgentsInteractor, LearningAgentsPolicy, nullptr, LearningAgentsTrainerSettings);
    }

}

// Called every frame
void ASphereLearningAgentsManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (SphereLearningAgentsTrainer != nullptr && LearningAgentsPolicy != nullptr) {

        // Turn off bTrain before start the training to play the learned policy
        if (bTrain && !bTrainDone) {

            // Small logic to detect the training ended and switch automaticaly to run the policy
            if (SphereLearningAgentsTrainer->IsTraining()) {
                bTrainInProgress = true;;
            }
            else if (bTrainInProgress && !SphereLearningAgentsTrainer->HasTrainingFailed()) {
                bTrainDone = true;
                SphereLearningAgentsTrainer->ResetEpisodes_Implementation(GetAllAgentIds());
            }

            if (!bTrainDone) {

                // Number of iteration for training, when done the policy is frozen and played (2000 enough for this simple task)
                LearningAgentsTrainerTrainingSettings.NumberOfIterations = 2000;

                // Switch to false if you want to re-train from scratch your policy (you might switch to off when you learn something with a lot of iterations)
                const bool bReinitializePolicyNetwork = true;

                // Defaults
                const bool bReinitializeCriticNetwork = true;
                const bool bResetAgentsOnBegin = true;

                SphereLearningAgentsTrainer->RunTraining(
                    LearningAgentsTrainerTrainingSettings, 
                    LearningAgentsTrainerGameSettings, 
                    LearningAgentsTrainerPathSettings, 
                    LearningAgentsCriticSettings, 
                    bReinitializePolicyNetwork, 
                    bReinitializeCriticNetwork, 
                    bResetAgentsOnBegin);

            }
        }
        else {
            LearningAgentsPolicy->RunInference();
        }
    }

}

