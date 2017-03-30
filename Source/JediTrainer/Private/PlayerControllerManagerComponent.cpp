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
	menuControllerComponent = NewObject<UMenuControllerComponent>(this, UMenuControllerComponent::StaticClass());
	menuControllerComponent->RegisterComponent();
	menuControllerComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	
}


// Called every frame
void UPlayerControllerManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerControllerManagerComponent::PressTrigger()
{
	// TODO: Call the active controller component's trigger method
}

void UPlayerControllerManagerComponent::PressGrip()
{

}

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

