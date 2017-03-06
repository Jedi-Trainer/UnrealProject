// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerHitbox.h"
#include "CylinderComponent.h"
#include "SkeletalPlayerHitboxComponent.generated.h"

/**
 * 
 */
UCLASS() class JEDITRAINER_API USkeletalPlayerHitboxComponent : public UPlayerHitboxComponent {
	GENERATED_BODY()
	
protected:
	// Initialize the cylinder components for each body part.
	UFUNCTION() void initHitboxCollider();

private:
	UPROPERTY() UCylinderComponent* headComponent;
	UPROPERTY() UCylinderComponent* chestComponent;
	UPROPERTY() UCylinderComponent* abdomenComponent;
	UPROPERTY() UCylinderComponent* pelvisComponent;

	UPROPERTY() FTransform chestTransform;
	UPROPERTY() FTransform abdomenTransform;
	UPROPERTY() FTransform pelvisTransform;
};
