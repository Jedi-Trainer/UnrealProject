// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "PlayerControllerComponent.h"
#include "MenuControllerComponent.h"
#include "PlayerControllerManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JEDITRAINER_API UPlayerControllerManagerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerControllerManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Input passed into controller manager from containing class
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") void PressTrigger();
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") void PressGrip();

private:
	UPROPERTY() UPlayerControllerComponent *menuControllerComponent;
	UPROPERTY() UPlayerControllerComponent *heldObjectControllerComponent;
	UPROPERTY() UPlayerControllerComponent *currentControllerComponent;
};
