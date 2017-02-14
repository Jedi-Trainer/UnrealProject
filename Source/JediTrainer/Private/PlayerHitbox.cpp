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

	// Update the alpha value of the UI Hit Display material. This is so it gradually fades out after you are hit.
	if (uIHitAlphaVal > 0) {
		uIHitAlphaVal -= 0.001;
	}
	hitDisplayMaterial->SetScalarParameterValue(FName(TEXT("UI_Hit_Alpha")), uIHitAlphaVal);;

	// ...
}

// Initialize the component to display when the player is hit
void UPlayerHitbox::initHitSphere() {
	redSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HitSphere"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("Material'/Game/Materials/UI_Hurt.UI_Hurt'"));
	
	if (SphereVisualAsset.Succeeded() && MaterialAsset.Succeeded())
	{
		// Store the material in a dynamic material instance so that we can update the alpha value
		hitDisplayMaterial = UMaterialInstanceDynamic::Create(MaterialAsset.Object, this);
		redSphere->SetStaticMesh(SphereVisualAsset.Object);
		redSphere->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		redSphere->SetWorldScale3D(FVector(0.8f));
		redSphere->SetMaterial(0, hitDisplayMaterial);
	} else {
		// Log an error - why can't I get this to work?
		// UE_LOG(LogTemp, ERROR, TEXT("Could not load player hit sphere"));
	}


}

// Set the visibility of the player hit component to true
void UPlayerHitbox::displayHit() {
	// Set the opacity of the UI Hit Display material to 0.5.
	uIHitAlphaVal = 0.5;
	
}
