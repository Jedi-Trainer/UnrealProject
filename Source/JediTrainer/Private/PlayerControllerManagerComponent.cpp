// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "PlayerControllerManagerComponent.h"


// Sets default values for this component's properties
UPlayerControllerManagerComponent::UPlayerControllerManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerControllerManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Instantiate menu controller
	/*
	menuControllerComponent = NewObject<UMenuControllerComponent>(this, UMenuControllerComponent::StaticClass());
	menuControllerComponent->RegisterComponent();
	menuControllerComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	*/
}


// Called every frame
void UPlayerControllerManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerControllerManagerComponent::PressTrigger()
{
	// Each controller component class should override this method.
	currentControllerComponent->PressTrigger();
}

void UPlayerControllerManagerComponent::PressGrip()
{
	// Each controller component class should override this method.
	currentControllerComponent->PressGrip();
}

// Sets the controller manager into menu mode or returns from menu mode
// TODO Currently, when menu mode is false the controller is returned to the held object state.
// If other states are to be implemented IE Force powers, blasters, then 'false' should return the controller
// manager to whichever state is appropriate.
void UPlayerControllerManagerComponent::SetMenuMode(bool isMenu)
{
	// Deactivate components
	menuControllerComponent->SetActiveControllerComponent(false);
	heldObjectControllerComponent->SetActiveControllerComponent(false);

	// Select new active component
	if (isMenu) 
	{
		currentControllerComponent = menuControllerComponent;
	}
	else if(heldObjectControllerComponent)
	{
		currentControllerComponent = heldObjectControllerComponent;
	}
	else 
	{
		// This case will be used when there is a default 'grabber' state the player uses to pick up a lightsaber.
		currentControllerComponent = NULL;
	}

	// Activate the controller component
	currentControllerComponent->SetActiveControllerComponent(true);
}

