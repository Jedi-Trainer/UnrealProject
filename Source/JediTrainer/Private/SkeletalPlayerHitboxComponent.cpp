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
	headComponent->SetVisible(true);

	chestComponent = NewObject<UCylinderComponent>(this, UCylinderComponent::StaticClass());
	chestComponent->RegisterComponent();
	chestComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	//chestComponent->SetScale(CHEST_SCALE_X, CHEST_SCALE_Y, CHEST_SCALE_Z);
	chestComponent->SetVisible(true);

	abdomenComponent = NewObject<UCylinderComponent>(this, UCylinderComponent::StaticClass());
	abdomenComponent->RegisterComponent();
	abdomenComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	//abdomenComponent->SetScale(ABDOMEN_SCALE_X, ABDOMEN_SCALE_Y, ABDOMEN_SCALE_Z);
	abdomenComponent->SetVisible(true);

	pelvisComponent = NewObject<UCylinderComponent>(this, UCylinderComponent::StaticClass());
	pelvisComponent->RegisterComponent();
	pelvisComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	//pelvisComponent->SetScale(PELVIS_SCALE_X, PELVIS_SCALE_Y, PELVIS_SCALE_Z);
	pelvisComponent->SetVisible(true);

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

}