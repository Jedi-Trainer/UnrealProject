// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerControllerComponent.h"
#include "LightsaberControllerComponent.generated.h"

/**
 * 
 */
UCLASS()
class JEDITRAINER_API ULightsaberControllerComponent : public UPlayerControllerComponent
{
	GENERATED_BODY()
	
	// TODO Add assets
	// TODO Override onTick()

protected:
	void onTriggerPressed() override;
	void onGripPressed() override;
	void onActiveControllerSet(bool isActive) override;

private:
	const FVector START_SCALE = FVector(0.0, 0.0, 0.0);
	const FVector END_SCALE = FVector(0.03, 0.03, 1.0);


	const float BLADE_LERP_RATE = 0.05; // Constant representing the scale of the interpolation rate.

	UPROPERTY() bool isLightsaberActive;
	UPROPERTY() bool isDead; // TODO Is this property redundant? Consult Blueprints prototype

	UPROPERTY() bool isLightsaberPaused; // TODO Check for use and consider for deletion

	UPROPERTY() FVector LastPosition; // TODO Check for use and consider for deletion

	// This value was called "Alpha" in the blueprints prototype. It refers to the current interpolation between the
	// fully deactivated state of the blade and the fully activated state.
	UPROPERTY() float BladeLerpAlpha;

	// This value was called "Delta" in the blueprints prototype. It refers to the rate at which the blade interpolation
	// is changing per frame. Should be negative BLADE_LERP_RATE, 0, or positive BLADE_LERP_RATE.
	UPROPERTY() float BladeLerpRate;

	// This was in the Blueprint prototype.
	// TODO Find out what this property was meant to do.
	UPROPERTY() float BaseSwingRate;





};
