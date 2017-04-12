// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "LightsaberControllerComponent.h"

void ULightsaberControllerComponent::onTriggerPressed()
{
	// Activate the lightsaber
	// TODO Unfinished
	if (!this->isDead) {
		this->isLightsaberActive = !this->isLightsaberActive;

		if (this->isLightsaberActive) 
		{
			this->BladeLerpRate = BLADE_LERP_RATE;

			// Play sound
			// TODO Add sounds
		}
		else
		{
			this->BladeLerpRate = -1 * BLADE_LERP_RATE;

			// Play sound
			// TODO Add sounds
		}

		// Activate force feedback on the controller, intensity 2.0, duration 0.5
		// TODO Implement force feedback
	}

}

void ULightsaberControllerComponent::onGripPressed()
{
	// Change the lightsaber color
	// TODO Unimplemented
}

void ULightsaberControllerComponent::onActiveControllerSet(bool isActive)
{
	// Disable and hide all components
	// TODO Unimplemented
}
