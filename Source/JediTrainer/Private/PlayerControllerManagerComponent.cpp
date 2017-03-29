// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "PlayerControllerManagerComponent.h"


// Sets default values for this component's properties
UPlayerControllerManagerComponent::UPlayerControllerManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Instantiate menu controller
	//menuControllerComponent = NewObject<UMenuControllerComponent>(this, UMenuControllerComponent::StaticClass());
	//menuControllerComponent->RegisterComponent();
	//menuControllerComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));

	// ...
}


// Called when the game starts
void UPlayerControllerManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
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

