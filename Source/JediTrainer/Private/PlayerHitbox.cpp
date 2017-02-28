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

	// The material should be set from within blueprints.
	/*
	ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Materials/UI_Hurt.UI_Hurt"));
	if (MaterialAsset.Succeeded())
	{
		if (MaterialAsset.Object == NULL) {
			UE_LOG(TraceLog, Warning, TEXT("Found NULL asset."));

		}

		hitDisplayMaterial = (MaterialAsset.Object);

		UE_LOG(TraceLog, Warning, TEXT("Material asset found successfully."));

		// Store the material in a dynamic material instance so that we can update the alpha value
		//hitDisplayMaterial = UMaterialInstanceDynamic::Create(MaterialAsset.Object, this);
		// TOOD: Why does it need two references to the object? Why does it crash otherwise?
		//hitDisplayMaterial = UMaterialInstanceDynamic::Create(MaterialAsset.Object, this);
		hitDisplayMaterialInstance = UMaterialInstanceDynamic::Create(hitDisplayMaterial, NULL);
	}
	*/

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
	if (health > 0) {
		if (uIHitAlphaVal > 0.0) {
			uIHitAlphaVal -= 0.01;
			// Why on Earth does this log produce and access violation?
			//UE_LOG(TraceLog, Warning, TEXT("TRACE: Material instance alpha value decremented: %s"), uIHitAlphaVal);
			//UE_LOG(TraceLog, Warning, TEXT("TRACE: Material instance alpha value decremented."));
			//if (hitDisplayMaterialInstance != NULL) {

			if (uIHitAlphaVal < 0.25) {
				redSphere->SetVisibility(false);
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
}

int UPlayerHitboxComponent::GetHealth()
{
	return health;
}

// Initialize the component to display when the player is hit
void UPlayerHitboxComponent::initHitDisplay() {
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Initializing hit display sphere."));
	//redSphere = NewObject<UStaticMeshComponent>(this, TEXT("HitSphere"));
	redSphere = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	redSphere->RegisterComponent();
	redSphere->SetStaticMesh(sphere);
	redSphere->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	//redSphere->SetWorldTransform(GetAttachmentRoot()->GetComponentTransform());
	//redSphere->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
	redSphere->SetWorldScale3D(FVector(0.8f));
	redSphere->SetVisibility(true);
	redSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	redSphere->SetCastShadow(false);

	if (hitDisplayMaterial != NULL) {
		redSphere->SetMaterial(0, hitDisplayMaterial);
		UE_LOG(TraceLog, Warning, TEXT("TRACE: Hit display sphere material set."));

		//hitDisplayMaterialInstance = redSphere->CreateAndSetMaterialInstanceDynamic(0);
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
	//capsuleCollider->SetWorldTransform(GetAttachmentRoot()->GetComponentTransform());
	capsuleCollider->SetVisibility(true);
	capsuleCollider->SetHiddenInGame(false);
	capsuleCollider->SetRelativeScale3D(FVector(SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR));
	//capsuleCollider->AddLocalOffset(FVector(0, 0, VERTICAL_OFFSET));
	capsuleCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// Bind on hit function to component hit event
	capsuleCollider->OnComponentHit.AddDynamic(this, &UPlayerHitboxComponent::onHit);
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Hitbox collider initialized."));
}

void UPlayerHitboxComponent::onHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Hitbox has been hit."));
	health -= 1;
	displayHit();
}


// Set the visibility of the player hit component to true
void UPlayerHitboxComponent::displayHit() {
	// Set the opacity of the UI Hit Display material to 0.5.
	uIHitAlphaVal = 1.0;
	redSphere->SetVisibility(true);
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Hit displayed."));
	
}
