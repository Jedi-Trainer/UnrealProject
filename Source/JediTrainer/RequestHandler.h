// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "UnrealString.h"
#include "RequestHandler.generated.h"

UCLASS()
class JEDITRAINER_API ARequestHandler : public AActor
{
	GENERATED_BODY()

public:
	FHttpModule * Http;

	/**
	UPROPERTY Notes:
	+ UPROPERTY enables the engine to preserve the value of the variable when launching the game or loading a saved level.
	+ UPROPERTY supports arguments that change how Unreal Engine will use the variable.
	+ Since we want our variable to be editable, we can add the EditAnywhere argument.
	+ (Translation: this will expose the variable outside, allowing us to set the value through the editor instead of hardcoding it!)
	+ Adding a comment allows for a small description that appears when you hover over the variable in the editor.
	*/

	/**
	UFUNCTION() Notes:
	+ There are three options to consider:
	1). BlueprintCallable functions are written in C++ and can be called from the Blueprint Graph, but cannot be changed or overridden without editing C++ code.
	Functions marked this way are usually features that have been programmed for non-programmer use, but that are not supposed to be changed or wouldn't make sense to change.
	An easy example of this would be any kind of math function.
	2). BlueprintImplementableEvent functions are set up in a C++ header (.h) file, but the body of the function is written entirely in the Blueprint Graph, not in C++.
	These are usually created to give a non-programmer the ability to create custom reactions to special situations that have no expected default action or standard behavior.
	An example of this might be an event that happens when a powerup touches the player's ship in a spaceship game.
	3). BlueprintNativeEvent functions are like a combination of BlueprintCallable and BlueprintImplementableEvent functions.
	They have default behaviors programmed in C++, but these can be supplemented or replaced by overriding in the Blueprint Graph. When programming these, the C++ code always goes in a virtual function with _Implementation added to the end of the name, as shown below.
	This is the most flexible option.
	*/

	//The actual HTTP call 
	UFUNCTION()
		void sendScore();

	// TODO: Rename GetScores() and GetScoreRecords() to be more intuitive. GetScores currently executes a GET request while GetScoreRecords is an accessor.
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") void GetScores();

	UFUNCTION(BlueprintCallable, Category = "Switch Functions") TArray<FString> GetScoreRecords();

	//Assign this function to call when the request processes successfully
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// Sets default values for this actor's properties
	ARequestHandler(const class FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY() TArray<FString> scoreRecords;


};
