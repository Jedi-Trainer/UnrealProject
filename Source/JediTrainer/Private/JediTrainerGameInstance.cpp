// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "JediTrainerGameInstance.h"

UJediTrainerGameInstance::UJediTrainerGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Default color index
	LightSaberColorIndex = 0;

	// Lowest difficulty
	Difficulty = 0;
}


