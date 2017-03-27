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
	headComponent->SetScale(HEAD_SCALE_X, HEAD_SCALE_Y, HEAD_SCALE_Z);
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
	chestTransform = FTransform(GetComponentRotation(), GetComponentLocation() + FVector(0, 0, CHEST_OFFSET), FVector(CHEST_SCALE_X, CHEST_SCALE_Y, CHEST_SCALE_Z));
	abdomenTransform = FTransform(GetComponentRotation(), GetComponentLocation() + FVector(0, 0, ABDOMEN_OFFSET), FVector(ABDOMEN_SCALE_X, ABDOMEN_SCALE_Y, ABDOMEN_SCALE_Z));
	pelvisTransform = FTransform(GetComponentRotation(), GetComponentLocation() + FVector(0, 0, PELVIS_OFFSET), FVector(PELVIS_SCALE_X, PELVIS_SCALE_Y, PELVIS_SCALE_Z));
}

// Called every frame
void USkeletalPlayerHitboxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Apply transforms
	if(chestComponent) chestComponent->SetWorldTransform(chestTransform);
	if(abdomenComponent) abdomenComponent->SetWorldTransform(abdomenTransform);
	if(pelvisComponent) pelvisComponent->SetWorldTransform(pelvisTransform);

	chestTransform = FTransform(
		FMath::Lerp(chestTransform.Rotator(), GetComponentRotation(), 0.5),
		FMath::Lerp(chestTransform.GetTranslation(), GetComponentLocation() + FVector(0, 0, CHEST_OFFSET), 0.5),
		FVector(CHEST_SCALE_X, CHEST_SCALE_Y, CHEST_SCALE_Z));

	abdomenTransform = FTransform(
		FMath::Lerp(chestTransform.Rotator(), pelvisTransform.Rotator(), 0.5),
		FMath::Lerp(chestTransform.GetTranslation(), pelvisTransform.GetTranslation(), 0.5),
		FVector(ABDOMEN_SCALE_X, ABDOMEN_SCALE_Y, ABDOMEN_SCALE_Z));

	pelvisTransform = FTransform(
		FRotator(0, 0, 0),
		FMath::Lerp(pelvisTransform.GetTranslation(), GetComponentLocation() + FVector(0, 0, PELVIS_OFFSET), 0.1),
		FVector(PELVIS_SCALE_X, PELVIS_SCALE_Y, PELVIS_SCALE_Z));

}

// Gets a random point on any hitbox cylinder for targeting
FVector USkeletalPlayerHitboxComponent::GetRandomPoint() {
	int cylinderNumber = FMath::RandRange(0, 3);
	switch (cylinderNumber)
	{
	case 0:
		return headComponent->GetRandomPoint();
		break;
	case 2:
		return abdomenComponent->GetRandomPoint();
		break;
	case 3:
		return pelvisComponent->GetRandomPoint();
		break;
	case 1:
	default:
		return chestComponent->GetRandomPoint();
		break;

	}

}