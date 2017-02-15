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

	// Precache models and materials
	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		sphere = SphereVisualAsset.Object;
	}
	ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Materials/UI_Hurt.UI_Hurt"));
	if (MaterialAsset.Succeeded())
	{
		// Store the material in a dynamic material instance so that we can update the alpha value
		//hitDisplayMaterial = UMaterialInstanceDynamic::Create(MaterialAsset.Object, this);
		// TOOD: Why does it need two references to the object? Why does it crash otherwise?
		hitDisplayMaterial = UMaterialInstanceDynamic::Create(MaterialAsset.Object, MaterialAsset.Object);
		
	}


}


// Called when the game starts
void UPlayerHitbox::BeginPlay()
{
	Super::BeginPlay();

	initHitDisplay();
	initHitboxCollider();

	// ...
	
}


// Called every frame
void UPlayerHitbox::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// If the player is not dead, update the alpha value of the UI Hit Display material. 
	// This is so it gradually fades out after you are hit.
	if (health > 0) {
		if (uIHitAlphaVal > 0) {
			uIHitAlphaVal -= 0.001;
		}
	//hitDisplayMaterial->SetScalarParameterValue(FName(TEXT("UI_Hit_Alpha")), uIHitAlphaVal);;
	}
}

int UPlayerHitbox::GetHealth()
{
	return health;
}

// Initialize the component to display when the player is hit
void UPlayerHitbox::initHitDisplay() {
	// redSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HitSphere"));
	redSphere = NewObject<UStaticMeshComponent>(this, TEXT("HitSphere"));

		
		redSphere->SetStaticMesh(sphere);
		redSphere->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		redSphere->SetWorldScale3D(FVector(0.8f));
		if (hitDisplayMaterial != NULL) {
			redSphere->SetMaterial(1, hitDisplayMaterial);
		}

}

// Initialize the component that collides with incoming objects.
void UPlayerHitbox::initHitboxCollider() {
	capsuleCollider = NewObject<UCapsuleComponent>(this, TEXT("HitboxCollider"));
	capsuleCollider->SetVisibility(false);
	capsuleCollider->SetRelativeScale3D(FVector(SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR));
	capsuleCollider->AddLocalOffset(FVector(0, 0, VERTICAL_OFFSET));
	// Bind on hit function to component hit event
	capsuleCollider->OnComponentHit.AddDynamic(this, &UPlayerHitbox::onHit);
}

void UPlayerHitbox::onHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	health -= 1;
	displayHit();
}


// Set the visibility of the player hit component to true
void UPlayerHitbox::displayHit() {
	// Set the opacity of the UI Hit Display material to 0.5.
	uIHitAlphaVal = 0.5;
	
}
