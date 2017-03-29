// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerHitbox.h"
#include "CylinderComponent.h"
#include "SkeletalPlayerHitboxComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class JEDITRAINER_API USkeletalPlayerHitboxComponent : public UPlayerHitboxComponent {
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Gets a random point on any hitbox cylinder for targeting
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") FVector GetRandomPoint();

protected:
	// Initialize the cylinder components for each body part.
	UFUNCTION() void initHitboxCollider() override;



private:
	// TODO Parameterize these constants
	const float HEAD_SCALE_X = 0.25;
	const float HEAD_SCALE_Y = 0.25;
	const float HEAD_SCALE_Z = 0.25;
	const float CHEST_SCALE_X = 0.35;
	const float CHEST_SCALE_Y = 0.35;
	const float CHEST_SCALE_Z = 0.25;
	const float ABDOMEN_SCALE_X = 0.35;
	const float ABDOMEN_SCALE_Y = 0.35;
	const float ABDOMEN_SCALE_Z = 0.25;
	const float PELVIS_SCALE_X = 0.35;
	const float PELVIS_SCALE_Y = 0.35;
	const float PELVIS_SCALE_Z = 0.25;
	const float CHEST_OFFSET = -25;
	const float ABDOMEN_OFFSET = -50;
	const float PELVIS_OFFSET = -75;

	UPROPERTY() UCylinderComponent* headComponent;
	UPROPERTY() UCylinderComponent* chestComponent;
	UPROPERTY() UCylinderComponent* abdomenComponent;
	UPROPERTY() UCylinderComponent* pelvisComponent;

	UPROPERTY() FTransform chestTransform;
	UPROPERTY() FTransform abdomenTransform;
	UPROPERTY() FTransform pelvisTransform;
	
};
