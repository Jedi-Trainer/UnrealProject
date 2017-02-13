// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "PlayerHitbox.h"

/**
 * PlayerHitbox Class
 *
 * Models a hitbox that can be used to approximate collisions with the player.
 * Should be used as a parent class for other hitboxes we may wish to use, including the skeletal hitbox.
 *
 */

// Sets default values for this component's properties
UPlayerHitbox::UPlayerHitbox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	health = STARTING_HEALTH;

	// ...
}


// Called when the game starts
void UPlayerHitbox::BeginPlay()
{
	Super::BeginPlay();
	initHitSphere();
	// ...
	
}


// Called every frame
void UPlayerHitbox::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

// Initialize the component to display when the player is hit
void UPlayerHitbox::initHitSphere() {
	redSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HitSphere"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("Material'/Game/Materials/UI_Hurt.UI_Hurt'"));
	if (SphereVisualAsset.Succeeded() && MaterialAsset.Succeeded())
	{
		redSphere->SetStaticMesh(SphereVisualAsset.Object);
		redSphere->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		redSphere->SetWorldScale3D(FVector(0.8f));
		redSphere->SetMaterial(0, MaterialAsset.Object);

		// Initialize the hit display component as invisible
		redSphere->SetVisibility(false);
	} else {
		// Log an error - why can't I get this to work?
		// UE_LOG(LogTemp, ERROR, TEXT("Could not load player hit sphere"));
	}


}

// Set the visibility of the player hit component to true
void UPlayerHitbox::displayHit() {
	redSphere->SetVisibility(true);
	// Wait 0.2 seconds before turning it off again
	// How do I do this?
	// Components may not access world timer manager.
	
}
