// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "SkeletalPlayerHitboxComponent.h"

// Initialize the components that collides with incoming objects.
void USkeletalPlayerHitboxComponent::initHitboxCollider(){
	// TODO Consider generalizing to an abritrarily sized array of cylinder components

	// Initialize cylinder components
	headComponent = NewObject<UCylinderComponent>(this, UCylinderComponent::StaticClass());
	headComponent->RegisterComponent();
	headComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	// headComponent->SetWorldScale3D(FVector(HeadScaleX, HeadScaleY, HeadScaleZ));
	headComponent->SetVisible(isVisibleDebug);

	chestComponent = NewObject<UCylinderComponent>(this, UCylinderComponent::StaticClass());
	chestComponent->RegisterComponent();
	chestComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	chestComponent->SetVisible(isVisibleDebug);

	abdomenComponent = NewObject<UCylinderComponent>(this, UCylinderComponent::StaticClass());
	abdomenComponent->RegisterComponent();
	abdomenComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	abdomenComponent->SetVisible(isVisibleDebug);

	pelvisComponent = NewObject<UCylinderComponent>(this, UCylinderComponent::StaticClass());
	pelvisComponent->RegisterComponent();
	pelvisComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	pelvisComponent->SetVisible(isVisibleDebug);

	// Bind on hit function to component hit events
	UStaticMeshComponent* headMesh = headComponent->GetStaticMeshComponent();
	headMesh->OnComponentHit.AddDynamic(this, &USkeletalPlayerHitboxComponent::onHit);
	UStaticMeshComponent* chestMesh = chestComponent->GetStaticMeshComponent();
	chestMesh->OnComponentHit.AddDynamic(this, &USkeletalPlayerHitboxComponent::onHit);
	UStaticMeshComponent* abdomenMesh = abdomenComponent->GetStaticMeshComponent();
	abdomenMesh->OnComponentHit.AddDynamic(this, &USkeletalPlayerHitboxComponent::onHit);
	UStaticMeshComponent* pelvisMesh = abdomenComponent->GetStaticMeshComponent();
	pelvisMesh->OnComponentHit.AddDynamic(this, &USkeletalPlayerHitboxComponent::onHit);

	// Initialize transforms
	headTransform = FTransform(
		GetComponentRotation(),
		GetComponentLocation(),
		FVector(HeadScaleX, HeadScaleY, HeadScaleZ));
	chestTransform = FTransform(GetComponentRotation(), GetComponentLocation() + FVector(0, 0, ChestOffset), FVector(ChestScaleX, ChestScaleY, ChestScaleZ));
	abdomenTransform = FTransform(GetComponentRotation(), GetComponentLocation() + FVector(0, 0, AbdomenOffset), FVector(AbdomenScaleX, AbdomenScaleY, AbdomenScaleZ));
	pelvisTransform = FTransform(GetComponentRotation(), GetComponentLocation() + FVector(0, 0, PelvisOffset), FVector(PelvisScaleX, PelvisScaleY, PelvisScaleZ));
}

// Called every frame
void USkeletalPlayerHitboxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Apply transforms
	if (headComponent) headComponent->SetWorldTransform(headTransform);
	if (chestComponent) chestComponent->SetWorldTransform(chestTransform);
	if (abdomenComponent) abdomenComponent->SetWorldTransform(abdomenTransform);
	if (pelvisComponent) pelvisComponent->SetWorldTransform(pelvisTransform);

	headTransform = FTransform(
		GetComponentRotation(),
		GetComponentLocation(),
		FVector(HeadScaleX, HeadScaleY, HeadScaleZ));

	chestTransform = FTransform(
		FMath::Lerp(chestTransform.Rotator(), headTransform.Rotator(), 0.5),
		FMath::Lerp(chestTransform.GetTranslation(), headTransform.GetTranslation() + FVector(0, 0, ChestOffset), 0.5),
		FVector(ChestScaleX, ChestScaleY, ChestScaleZ));

	abdomenTransform = FTransform(
		FMath::Lerp(chestTransform.Rotator(), pelvisTransform.Rotator(), 0.5),
		FMath::Lerp(chestTransform.GetTranslation(), pelvisTransform.GetTranslation(), 0.5),
		FVector(AbdomenScaleX, AbdomenScaleY, AbdomenScaleZ));

	pelvisTransform = FTransform(
		FRotator(0, 0, 0),
		FMath::Lerp(pelvisTransform.GetTranslation(), headTransform.GetTranslation() + FVector(0, 0, PelvisOffset), 0.1),
		FVector(PelvisScaleX, PelvisScaleY, PelvisScaleZ));

}

// Gets a random point on any hitbox cylinder for targeting
FVector USkeletalPlayerHitboxComponent::GetRandomPoint() {
	int cylinderNumber = FMath::RandRange(0, 3);
	UE_LOG(TraceLog, Warning, TEXT("TRACE: Randomly selected cylinder: %i"), cylinderNumber);
	switch (cylinderNumber)
	{
	case 0:
		return headComponent->GetRandomPoint();
	case 2:
		return abdomenComponent->GetRandomPoint();
	case 3:
		return pelvisComponent->GetRandomPoint();
	case 1:
	default:
		return chestComponent->GetRandomPoint();
	}

}