// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "CubeSceneComponent.h"


// Sets default values for this component's properties
UCubeSceneComponent::UCubeSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Precache models and materials
	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (CubeVisualAsset.Succeeded())
	{
		cubeMesh = CubeVisualAsset.Object;
	}

	// ...
}


// Called when the game starts
void UCubeSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	cubeMeshComponent = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this, TEXT("CubeStaticMeshComponent"));
	if (cubeMeshComponent)
	{
		cubeMeshComponent->RegisterComponent();
		//cubeMeshComponent->SetRelativeLocation(Location);
		//cubeMeshComponent->SetRelativeRotation(Rotation);
		//cubeMeshComponent->AttachTo(RootComponent, NAME_None, EAttachLocation::KeepRelativeOffset);
		cubeMeshComponent->SetStaticMesh(cubeMesh);
	}
	// ...
	
}


// Called every frame
void UCubeSceneComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

