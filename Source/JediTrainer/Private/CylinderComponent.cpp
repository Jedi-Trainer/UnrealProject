// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "CylinderComponent.h"


// Sets default values for this component's properties
UCylinderComponent::UCylinderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Precache models and materials
	ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (CylinderVisualAsset.Succeeded())
	{
		cylinder = CylinderVisualAsset.Object;
	}

	// ...
}


// Called when the game starts
void UCylinderComponent::BeginPlay()
{
	Super::BeginPlay();

	cylinderMeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	cylinderMeshComponent->RegisterComponent();
	cylinderMeshComponent->SetStaticMesh(cylinder);
	cylinderMeshComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	cylinderMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	cylinderMeshComponent->SetCastShadow(false);

	// ...
	
}


// Called every frame
void UCylinderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// This method returns a random point on the cylinder.
FVector UCylinderComponent::GetRandomPoint() {
	// Unimplemented
	return FVector(0.0, 0.0, 0.0);
}

// Get the static mesh component of this CylinderComponent.
UStaticMeshComponent* UCylinderComponent::GetStaticMeshComponent() {
	return cylinderMeshComponent;
}

void UCylinderComponent::SetVisible(bool isVisible) {
	cylinderMeshComponent->SetVisibility(isVisible);
}