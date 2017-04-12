// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "PlayerControllerComponent.generated.h"

// This class my be inherited by C++ classes or by Blueprint classes.
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UPlayerControllerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerControllerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void onTriggerPressed();
	virtual void onGripPressed();
	virtual void onActiveControllerSet(bool isActive);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Input from Controller Manager
	UFUNCTION(BlueprintNativeEvent, Category = "Controller Input Functions") void PressTrigger();
	UFUNCTION(BlueprintNativeEvent, Category = "Controller Input Functions") void PressGrip();

	// Method to toggle this controller active
	UFUNCTION(BlueprintNativeEvent, Category = "Controller Input Functions") void SetActiveControllerComponent(bool isActive);
		
	
};
