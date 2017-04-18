// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PlayerHitboxComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JEDITRAINER_API UPlayerHitboxComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerHitboxComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Should the hitbox itself be visible
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering") bool isVisibleDebug;

	// Accessor for health variable
	UFUNCTION(BlueprintCallable, Category= "Switch Functions") int GetHealth();

	// Property for hit display material
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material") UMaterial* hitDisplayMaterial;

protected:
	// Initialize the component that collides with incoming objects.
	UFUNCTION() virtual void initHitboxCollider();

	// Function to be called upon collision with another object.
	UFUNCTION() void onHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


private:
	// Constant representing the beginning health the player should have
	// TODO Consider parameterizing this field so that it can be modified outside of the game mode
	// TODO Should this be accessed through the game instance?
	const int STARTING_HEALTH = 5;
	const float SCALE_FACTOR = 1.5;
	const float VERTICAL_OFFSET = -30;


	// Store health variable
	UPROPERTY() int health;

	// Red screen effect when hit
	UFUNCTION() void displayHit();

	// Sphere to render in order to show the player has been hit
	UPROPERTY() UStaticMeshComponent* hitDisplaySphere;
	 
	// Capsule collision component
	UPROPERTY() UCapsuleComponent* capsuleCollider;

	// Initialize the component that displays when the player is hit
	UFUNCTION() void initHitDisplay();

	// Material instance used to store the UI Hit effect
	UPROPERTY() UMaterialInstanceDynamic* hitDisplayMaterialInstance;

	// Variable to store the current opacity
	UPROPERTY() float uIHitAlphaVal;

	// Sphere model
	UPROPERTY() UStaticMesh* sphere;
};
