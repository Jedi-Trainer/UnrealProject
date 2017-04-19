// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "PlayerHitboxComponent.h"

/**
 * PlayerHitbox Class
 *
 * Models a hitbox that can be used to approximate collisions with the player.
 * Should be used as a parent class for other hitboxes we may wish to use, including the skeletal hitbox.
 *
 */

// Sets default values for this component's properties
UPlayerHitboxComponent::UPlayerHitboxComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	health = STARTING_HEALTH;
	uIHitAlphaVal = 1.0;

	// Precache models and materials
	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		sphere = SphereVisualAsset.Object;
	}

}


// Called when the game starts
void UPlayerHitboxComponent::BeginPlay()
{
	Super::BeginPlay();

	initHitDisplay();
	initHitboxCollider();

	// ...
	
}


// Called every frame
void UPlayerHitboxComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// If the player is not dead, update the alpha value of the UI Hit Display material. 
	// This is so it gradually fades out after you are hit.
		if (uIHitAlphaVal > 0.0) {
			uIHitAlphaVal -= 0.03;
			// Why on Earth does this log produce and access violation?
			//UE_LOG(TraceLog, Warning, TEXT("TRACE: Material instance alpha value decremented: %s"), uIHitAlphaVal);
			//UE_LOG(TraceLog, Warning, TEXT("TRACE: Material instance alpha value decremented."));
			//if (hitDisplayMaterialInstance != NULL) {

			if (uIHitAlphaVal < 0.25) {
				hitDisplaySphere->SetVisibility(false);
			}

			//UMaterialInstanceDynamic* Mat_Inst = redSphere->CreateAndSetMaterialInstanceDynamic(0);

			//Mat_Inst->SetScalarParameterValue(FName("UI_Hit_Alpha"), 1.0);
			//hitDisplayMaterialInstance->SetScalarParameterValue(FName("UI_Hit_Alpha"), 1.0);
				//hitDisplayMaterialInstance->SetScalarParameterByIndex(0, uIHitAlphaVal);
				// Why? - I suspect that because the variable wasn't declared with an Unreal directive, the engine was garbage collecting it.
			//UE_LOG(TraceLog, Warning, TEXT("TRACE: Material instance scalar parameters set."));
		
			//}
		}
}

int UPlayerHitboxComponent::GetHealth()
{
	return health;
}

// Initialize the component to display when the player is hit
void UPlayerHitboxComponent::initHitDisplay() {
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Initializing hit display sphere."));
	hitDisplaySphere = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	hitDisplaySphere->RegisterComponent();
	hitDisplaySphere->SetStaticMesh(sphere);
	hitDisplaySphere->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	hitDisplaySphere->SetWorldScale3D(FVector(0.8f));
	hitDisplaySphere->SetVisibility(false);
	hitDisplaySphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	hitDisplaySphere->SetCastShadow(false);
	hitDisplaySphere->SetRelativeLocation(FVector(0, 0, -25));

	if (hitDisplayMaterial != NULL) {
		hitDisplaySphere->SetMaterial(0, hitDisplayMaterial);
		UE_LOG(TraceLog, Warning, TEXT("TRACE: Hit display sphere material set."));
		UE_LOG(TraceLog, Warning, TEXT("Material instance created successfully."));
	}
	else {
		UE_LOG(TraceLog, Warning, TEXT("WARNING: Hit display material is null."));
	}

	

}

// Initialize the component that collides with incoming objects.
void UPlayerHitboxComponent::initHitboxCollider() {
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Hitbox collider initializing..."));
	capsuleCollider = NewObject<UCapsuleComponent>(this, UCapsuleComponent::StaticClass());
	capsuleCollider->RegisterComponent();
	capsuleCollider->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	capsuleCollider->SetVisibility(isVisibleDebug);
	capsuleCollider->SetHiddenInGame(false);
	capsuleCollider->SetRelativeScale3D(FVector(SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR));
	capsuleCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// Bind on hit function to component hit event
	capsuleCollider->OnComponentHit.AddDynamic(this, &UPlayerHitboxComponent::onHit);
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Hitbox collider initialized."));
}

void UPlayerHitboxComponent::onHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Hitbox has been hit."));
	// Only take damage if the hit display is at less than 50% opacity.
	// This is so that the player never takes damage while the hit indicator is still visible.
	if (uIHitAlphaVal < 0.5)
	{
		health -= 1;
		displayHit();
	}
}


// Set the visibility of the player hit component to true
void UPlayerHitboxComponent::displayHit() {
	// Set the opacity of the UI Hit Display material to 0.5.
	uIHitAlphaVal = 1.0;
	hitDisplaySphere->SetVisibility(true);
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Hit displayed."));
	
}
