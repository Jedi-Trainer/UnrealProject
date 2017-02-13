// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PlayerHitbox.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JEDITRAINER_API UPlayerHitbox : public UActorComponent
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
	int GetHealth();


private:
	// Constant representing the beginning health the player should have
	// Consider parameterizing this field so that it can be modified outside of the game mode
	const int STARTING_HEALTH = 20;


	// Store health variable
	int health;

	// Red screen effect when hit
	void displayHit();

	// Sphere to render in order to show the player has been hit
	UStaticMeshComponent* redSphere;

	// Initialize the component that displays when the player is hit
	void initHitSphere();

};
