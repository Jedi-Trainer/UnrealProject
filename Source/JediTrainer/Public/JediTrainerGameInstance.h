// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "JediTrainerGameInstance.generated.h"

/**
 * https://github.com/Jedi-Trainer/UnrealProject/wiki/JediTrainerGameInstance
 * JediTrainerGameInstance defines the game instance data. 
 * The game instance can be accessed globally and stores data which persists between levels.
 */
UCLASS()
class JEDITRAINER_API UJediTrainerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UJediTrainerGameInstance(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Game Configuration")
		int32 LightSaberColorIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Configuration")
		int32 Difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Configuration")
		FName currentLevel;
	
};
