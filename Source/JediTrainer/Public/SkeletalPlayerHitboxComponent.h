// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerHitboxComponent.h"
#include "CylinderComponent.h"
#include "SkeletalPlayerHitboxComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable, Config=Game) class JEDITRAINER_API USkeletalPlayerHitboxComponent : public UPlayerHitboxComponent {
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
	const float HeadScaleX = 0.20;
	const float HeadScaleY = 0.20;
	const float HeadScaleZ = 0.20;
	const float ChestScaleX = 0.35;
	const float ChestScaleY = 0.35;
	const float ChestScaleZ = 0.25;
	const float AbdomenScaleX = 0.35;
	const float AbdomenScaleY = 0.35;
	const float AbdomenScaleZ = 0.25;
	const float PelvisScaleX = 0.35;
	const float PelvisScaleY = 0.35;
	const float PelvisScaleZ = 0.25;
	const float ChestOffset = -25;
	const float AbdomenOffset = -50;
	const float PelvisOffset = -75;

	UPROPERTY() UCylinderComponent* headComponent;
	UPROPERTY() UCylinderComponent* chestComponent;
	UPROPERTY() UCylinderComponent* abdomenComponent;
	UPROPERTY() UCylinderComponent* pelvisComponent;

	UPROPERTY() FTransform headTransform;
	UPROPERTY() FTransform chestTransform;
	UPROPERTY() FTransform abdomenTransform;
	UPROPERTY() FTransform pelvisTransform;
	
};
