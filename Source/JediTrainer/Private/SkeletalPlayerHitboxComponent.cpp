// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "SkeletalPlayerHitboxComponent.h"


// Initialize the components that collides with incoming objects.
void USkeletalPlayerHitboxComponent::initHitboxCollider(){
	
	headComponent = NewObject<UCylinderComponent>(this, UCylinderComponent::StaticClass());
	
	// Bind on hit function to component hit events
	UStaticMeshComponent* headMesh = headComponent->GetStaticMeshComponent();
	headMesh->OnComponentHit.AddDynamic(this, &USkeletalPlayerHitboxComponent::onHit);
	UStaticMeshComponent* chestMesh = chestComponent->GetStaticMeshComponent();
	chestMesh->OnComponentHit.AddDynamic(this, &USkeletalPlayerHitboxComponent::onHit);
	UStaticMeshComponent* abdomenMesh = abdomenComponent->GetStaticMeshComponent();
	abdomenMesh->OnComponentHit.AddDynamic(this, &USkeletalPlayerHitboxComponent::onHit);
	UStaticMeshComponent* pelvisMesh = abdomenComponent->GetStaticMeshComponent();
	pelvisMesh->OnComponentHit.AddDynamic(this, &USkeletalPlayerHitboxComponent::onHit);
}

