// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "CylinderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JEDITRAINER_API UCylinderComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCylinderComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Get a random point on this cylinder.
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") FVector GetRandomPoint();
	
	// Get static mesh component.
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") UStaticMeshComponent* GetStaticMeshComponent();

	// Set the visibility of the cylinder.
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") void SetVisible(bool isVisible);

private:
	// Cylinder model
	UPROPERTY() UStaticMesh* cylinder;
	
	// Static mesh component
	UPROPERTY() UStaticMeshComponent* cylinderMeshComponent;

};
