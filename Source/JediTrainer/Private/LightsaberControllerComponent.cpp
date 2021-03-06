// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "LightsaberControllerComponent.h"

ULightsaberControllerComponent::ULightsaberControllerComponent() 
{
	// Load assets
	// TODO We should find some way to offload this step to Unreal. However I did not want to pass assets through the
	// PlayerControllerManagerComponent. Perhaps the VRPawn should own each possible controller and pass that to the manager?
	// In any case, it will need to be revisited to remove code duplication from this constructor and ensure durability.

	ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderVisualAsset(ANSI_TO_TCHAR(bladeMeshAssetPath));
	if (CylinderVisualAsset.Succeeded())
	{
		this->bladeMesh = CylinderVisualAsset.Object;
		UE_LOG(TraceLog, Warning, TEXT("TRACE: Blade mesh loaded."));
	} 
	else 
	{
		UE_LOG(TraceLog, Warning, TEXT("WARNING: Blade mesh could not be loaded."));
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> HiltVisualAsset(ANSI_TO_TCHAR(hiltMeshAssetPath));
	if (HiltVisualAsset.Succeeded())
	{
		this->hiltMesh = HiltVisualAsset.Object;
		UE_LOG(TraceLog, Warning, TEXT("TRACE: Hilt mesh loaded."));
	}
	else
	{
		UE_LOG(TraceLog, Warning, TEXT("WARNING: Hilt mesh could not be loaded."));
	}

	ConstructorHelpers::FObjectFinder<UMaterial> LightsaberHiltTextureAsset(ANSI_TO_TCHAR(hiltMaterialAssetPath));
	if (LightsaberHiltTextureAsset.Succeeded())
	{
		this->hiltMaterial = LightsaberHiltTextureAsset.Object;
		UE_LOG(TraceLog, Warning, TEXT("TRACE: Hilt material loaded."));
	}
	else
	{
		UE_LOG(TraceLog, Warning, TEXT("WARNING: Blue blade material could not be loaded."));
	}

	ConstructorHelpers::FObjectFinder<UMaterial> BlueBladeTextureAsset(ANSI_TO_TCHAR(bladeTextureAssetPath_Blue));
	if (BlueBladeTextureAsset.Succeeded())
	{
		this->bladeMaterialBlue = BlueBladeTextureAsset.Object;
		UE_LOG(TraceLog, Warning, TEXT("TRACE: Blue blade material loaded."));
	}
	else
	{
		UE_LOG(TraceLog, Warning, TEXT("WARNING: Blue blade material could not be loaded."));
	}

	ConstructorHelpers::FObjectFinder<UMaterial> GreenBladeTextureAsset(ANSI_TO_TCHAR(bladeTextureAssetPath_Green));
	if (GreenBladeTextureAsset.Succeeded())
	{
		this->bladeMaterialGreen = GreenBladeTextureAsset.Object;
		UE_LOG(TraceLog, Warning, TEXT("TRACE: Green blade material loaded."));
	}
	else
	{
		UE_LOG(TraceLog, Warning, TEXT("WARNING: Green blade material could not be loaded."));
	}

	ConstructorHelpers::FObjectFinder<UMaterial> RedBladeTextureAsset(ANSI_TO_TCHAR(bladeTextureAssetPath_Red));
	if (RedBladeTextureAsset.Succeeded())
	{
		this->bladeMaterialRed = RedBladeTextureAsset.Object;
		UE_LOG(TraceLog, Warning, TEXT("TRACE: Red blade material loaded."));
	}
	else
	{
		UE_LOG(TraceLog, Warning, TEXT("WARNING: Red blade material could not be loaded."));
	}

	ConstructorHelpers::FObjectFinder<UMaterial> PurpleBladeTextureAsset(ANSI_TO_TCHAR(bladeTextureAssetPath_Purple));
	if (RedBladeTextureAsset.Succeeded())
	{
		this->bladeMaterialPurple = PurpleBladeTextureAsset.Object;
		UE_LOG(TraceLog, Warning, TEXT("TRACE: Purple blade material loaded."));
	}
	else
	{
		UE_LOG(TraceLog, Warning, TEXT("WARNING: Purple blade material could not be loaded."));
	}
}

void ULightsaberControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(TraceLog, Warning, TEXT("TRACE: Initializing lightsaber hilt."));
	hiltComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	hiltComponent->RegisterComponent();
	hiltComponent->SetStaticMesh(hiltMesh);
	hiltComponent->SetVisibility(true);
	hiltComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	hiltComponent->SetCastShadow(true);
	hiltComponent->SetWorldTransform(FTransform(HiltRotation, HiltLocation, HiltScale));
	
	hiltComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

	if (hiltMaterial != NULL) {
		hiltComponent->SetMaterial(0, hiltMaterial);
		UE_LOG(TraceLog, Warning, TEXT("TRACE: Lightsaber hilt material set."));
	}
	else {
		UE_LOG(TraceLog, Warning, TEXT("WARNING: Lightsaber hilt material is null."));
	}

	UE_LOG(TraceLog, Warning, TEXT("TRACE: Initializing lightsaber blade."));
	bladeComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	bladeComponent->RegisterComponent();
	bladeComponent->SetStaticMesh(bladeMesh);
	bladeComponent->SetVisibility(true);
	bladeComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bladeComponent->SetCastShadow(false);
	bladeComponent->SetWorldTransform(FTransform(BladeRotation, BladeLocation, BladeScale));

	bladeComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

	if (bladeMaterialBlue != NULL) {
		bladeComponent->SetMaterial(0, bladeMaterialBlue);
		UE_LOG(TraceLog, Warning, TEXT("TRACE: Lightsaber blade material set."));
	}
	else {
		UE_LOG(TraceLog, Warning, TEXT("WARNING: Lightsaber blade material is null."));
	}
}

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
