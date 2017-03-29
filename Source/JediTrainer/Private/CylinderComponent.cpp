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
	cylinderMeshComponent->SetWorldTransform(cylinderTransform);
	// ...
}

// This method returns a random point on the cylinder.
FVector UCylinderComponent::GetRandomPoint() {
	// Get the scale of the mesh
	FVector scale = cylinderMeshComponent->GetComponentTransform().GetScale3D();
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Cylinder scale vector: %s"), *scale.ToString());
	// Find the origin point
	float cylinderRadius = 50;
	
	float originX = cylinderTransform.GetLocation().X;
	float originY = cylinderTransform.GetLocation().Y;
	float originZ = cylinderTransform.GetLocation().Z;

	FVector origin = FVector(originX, originY, originZ);
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Cylinder origin vector: %s"), *origin.ToString());

	// First find a random point on the cylinder assuming it is aligned along the z axis at the component position
	float randX = FMath::RandRange(originX - cylinderRadius *  scale.X, originX + cylinderRadius * scale.X);
	float randY = FMath::RandRange(originY - cylinderRadius *  scale.Y, originY + cylinderRadius * scale.Y);
	float randZ = FMath::RandRange(originZ - cylinderRadius *  scale.Z, originZ + cylinderRadius * scale.Z);
	FVector randomPoint = FVector(randX, randY, randZ);

	// Next, rotate the point about each axis given the angles from the component rotator
	FVector rotation = cylinderTransform.GetRotation().Euler();
	
	// The following rotations seem to project the points outside of the cylinder.
	// TODO Test and see if the points are actually projected within the cylinder.
	randomPoint = randomPoint.RotateAngleAxis(rotation.X, FVector(1, 0, 0));
	randomPoint = randomPoint.RotateAngleAxis(rotation.Y, FVector(0, 1, 0));
	randomPoint = randomPoint.RotateAngleAxis(rotation.Z, FVector(0, 0, 1));

	// Return the point rotated about the angles
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Found random point on hitbox: %s"), *randomPoint.ToString());
	return randomPoint;
}

// Get the static mesh component of this CylinderComponent.
UStaticMeshComponent* UCylinderComponent::GetStaticMeshComponent() {
	return cylinderMeshComponent;
}

void UCylinderComponent::SetVisible(bool isVisible) {
	SetVisibility(isVisible);
	cylinderMeshComponent->SetVisibility(isVisible);
}

// Sets the scale of the cylinder mesh component given three float values
void UCylinderComponent::SetScale(float w, float d, float h) {
	cylinderMeshComponent->SetRelativeScale3D(FVector(w, d, h));
}

// Sets a new world transform for the cylinder mesh component
void UCylinderComponent::SetWorldTransform(FTransform newTransform) {
	cylinderTransform = newTransform;
}