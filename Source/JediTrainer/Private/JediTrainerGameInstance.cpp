// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "JediTrainerGameInstance.h"

UJediTrainerGameInstance::UJediTrainerGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Default color index
	LightSaberColorIndex = 3;

	// Lowest difficulty
	Difficulty = 0;

	// Default level
	currentLevel = TEXT("Tatooine");
}


