// Fill out your copyright notice in the Description page of Project Settings.


#include "SpherePawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpherePawn::ASpherePawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpherePawn::BeginPlay()
{
    Super::BeginPlay();

    const auto comps = GetComponents();
    for (const auto& c : comps) {
        if (UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(c)) {
            if (MeshComponent->GetName() == "Sphere") {
                StaticMeshComponent = MeshComponent;
            }
        }
    }

    TArray<AActor*> Actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);
    for (const auto& Actor : Actors) {
        if (Actor->GetName().Contains("PlayerStart"))
        {
            PlayerStartActor = Actor;
        }
    }
}

// Called every frame
void ASpherePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ActualVelocity = GetSphereVelocity();
}

// Called to bind functionality to input
void ASpherePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASpherePawn::MoveX(const float value)
{
    if (StaticMeshComponent != nullptr) {
        StaticMeshComponent->AddForce(FVector(value, 0.0f, 0.0f));
    }

}

void ASpherePawn::MoveY(const float value)
{
    if (StaticMeshComponent != nullptr) {
        StaticMeshComponent->AddForce(FVector(0.0f, value, 0.0f));
    }
}

const FVector ASpherePawn::GetSphereVelocity() const
{
    if (StaticMeshComponent != nullptr) {
        return StaticMeshComponent->GetComponentVelocity();
    }
    return FVector::Zero();
}

void ASpherePawn::ResetPosition()
{
    if (StaticMeshComponent != nullptr && PlayerStartActor != nullptr) {
        StaticMeshComponent->SetWorldLocation(PlayerStartActor->GetActorLocation());
        StaticMeshComponent->SetPhysicsLinearVelocity(FVector::Zero());
        StaticMeshComponent->SetPhysicsAngularVelocityInRadians(FVector::Zero());
    }
}
