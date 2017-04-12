// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "PlayerControllerComponent.h"


// Sets default values for this component's properties
UPlayerControllerComponent::UPlayerControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPlayerControllerComponent::onTriggerPressed()
{
}

void UPlayerControllerComponent::onGripPressed()
{
}

void UPlayerControllerComponent::onActiveControllerSet(bool isActive)
{
}


// Called every frame
void UPlayerControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// The body of these functions are defined by "<FunctionName>_Implementation" because they are Blueprint Native
// functions, which means that they have a definition in C++ but can be overridden in blueprints.
void UPlayerControllerComponent::PressTrigger_Implementation()
{
	onTriggerPressed();
}

// The body of these functions are defined by "<FunctionName>_Implementation" because they are Blueprint Native
// functions, which means that they have a definition in C++ but can be overridden in blueprints.
void UPlayerControllerComponent::PressGrip_Implementation()
{
	onGripPressed();
}

// The body of these functions are defined by "<FunctionName>_Implementation" because they are Blueprint Native
// functions, which means that they have a definition in C++ but can be overridden in blueprints.
void UPlayerControllerComponent::SetActiveControllerComponent_Implementation(bool isActive)
{
	onActiveControllerSet(isActive);
}