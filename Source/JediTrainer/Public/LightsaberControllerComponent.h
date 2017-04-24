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

public:
	ULightsaberControllerComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	void onTriggerPressed() override;
	void onGripPressed() override;
	void onActiveControllerSet(bool isActive) override;

private:
	UPROPERTY() UStaticMeshComponent* bladeComponent;
	UPROPERTY() UStaticMeshComponent* hiltComponent;

	// Assets
	UPROPERTY() UStaticMesh* bladeMesh;
	UPROPERTY() UStaticMesh* hiltMesh;
	UPROPERTY() UMaterial* hiltMaterial;
	UPROPERTY() UMaterial* bladeMaterialBlue;
	UPROPERTY() UMaterial* bladeMaterialGreen;
	UPROPERTY() UMaterial* bladeMaterialRed;
	UPROPERTY() UMaterial* bladeMaterialPurple;

	// Constants
	// TODO Make config file
	const FVector START_SCALE = FVector(0.0, 0.0, 0.0);
	const FVector END_SCALE = FVector(0.03, 0.03, 1.0);
	const float BLADE_LERP_RATE = 0.05; // Constant representing the scale of the interpolation rate.
	// const FVector HiltLocation = FVector(-0.5, -7.6, 17.0);
	const FVector HiltLocation = FVector(0, 0, 0);
	const FRotator HiltRotation = FRotator(270, -90.0, 0);
	const FVector HiltScale = FVector(0.04, 0.04, 0.04);
	const FVector BladeLocation = FVector(0.0, 0.0, 27.0);
	const FRotator BladeRotation = FRotator(0.0, 0.0, 0.0);
	const FVector BladeScale = END_SCALE;
	const char* bladeMeshAssetPath = "/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder";
	const char* bladeTextureAssetPath_Blue = "/Game/Materials/Lightsaber2.Lightsaber2";
	const char* bladeTextureAssetPath_Green = "/Game/Materials/Lightsaber_ROJ.Lightsaber_ROJ";
	const char* bladeTextureAssetPath_Red = "/Game/Materials/Lightsaber_Vader.Lightsaber_Vader";
	const char* bladeTextureAssetPath_Purple = "/Game/Materials/Lightsaber_Windu.Lightsaber_Windu";
	const char* hiltMeshAssetPath = "/Game/Models/saber_model.saber_model";
	const char* hiltMaterialAssetPath = "/Game/Materials/LightsaberHiltMaterial.LightsaberHiltMaterial";
	// const FString hiltTextAssetPath;

	// Properties
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
