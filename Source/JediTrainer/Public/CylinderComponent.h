// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "CylinderComponent.generated.h"

/**
 * https://github.com/Jedi-Trainer/UnrealProject/wiki/CylinderComponent
 * CylinderComponent models an untextured cylinder with collisions. It provides a method, GetRandomPoint() that will return a random point on the cylinder.
 * This class was written for the skeletal hitbox player collision system. (See: SkeletalPlayerHitboxComponent)
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JEDITRAINER_API UCylinderComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCylinderComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Get a random point on this cylinder.
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") FVector GetRandomPoint();
	
	// Get static mesh component.
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") UStaticMeshComponent* GetStaticMeshComponent();

	// Set the visibility of the cylinder.
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") void SetVisible(UPARAM(DisplayName = "Is Visible") bool isVisible);

	// Set the scale of the cylinder transform
	// TODO Would it be preferable to take in a vector?
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") void SetScale(
		UPARAM(DisplayName = "Width") float w, // Corresponds to x axis
		UPARAM(DisplayName = "Depth") float d, // Corresponds to y axis
		UPARAM(DisplayName = "Height") float h // Corresponds to z axis
		);

	// Sets the world transform of the cylinder to the given transform. Ignores parenting.
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") void SetWorldTransform(
		UPARAM(DisplayName = "World Transform") FTransform newTransform);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Cylinder model
	UPROPERTY() UStaticMesh* cylinder;

	// Transform
	UPROPERTY() FTransform cylinderTransform;
	
	// Static mesh component
	UPROPERTY() UStaticMeshComponent* cylinderMeshComponent;

};
