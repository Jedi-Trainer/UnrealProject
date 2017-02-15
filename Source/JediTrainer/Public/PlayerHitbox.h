// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PlayerHitbox.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JEDITRAINER_API UPlayerHitbox : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerHitbox();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Accessor for health variable
	UFUNCTION(BlueprintCallable, Category= "Switch Functions") int GetHealth();


private:
	// Constant representing the beginning health the player should have
	// Consider parameterizing this field so that it can be modified outside of the game mode
	const int STARTING_HEALTH = 20;
	const float SCALE_FACTOR = 1.5;
	const float VERTICAL_OFFSET = -30;


	// Store health variable
	int health;

	// Red screen effect when hit
	void displayHit();

	// Sphere to render in order to show the player has been hit
	UStaticMeshComponent* redSphere;

	// Capsule collision component
	UCapsuleComponent* capsuleCollider;

	// Initialize the component that displays when the player is hit
	void initHitDisplay();

	// Initialize the component that collides with incoming objects.
	void initHitboxCollider();

	// Material instance used to store the UI Hit effect
	UMaterialInstanceDynamic* hitDisplayMaterial;

	// Variable to store the current opacity
	float uIHitAlphaVal = 0.0;

	// Function to be called upon collision with another object.
	UFUNCTION() void onHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Sphere model
	UStaticMesh* sphere;
};
