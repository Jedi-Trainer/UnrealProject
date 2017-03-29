// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "PlayerHitboxActor.h"


// Sets default values
APlayerHitboxActor::APlayerHitboxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerHitboxActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerHitboxActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

