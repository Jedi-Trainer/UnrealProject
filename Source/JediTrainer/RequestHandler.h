// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "UnrealString.h"
#include "RequestHandler.generated.h"

/**
 * RequestHandler
 * https://github.com/Jedi-Trainer/UnrealProject/wiki/RequestHandler
 * RequestHandler communicates with the remote Jedi Trainer web server and stores information for the game's leaderboard, including the currently viewed scores and rank of the player on the current leaderboard. 
 */

UCLASS()
class JEDITRAINER_API ARequestHandler : public AActor
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReceivedScoreRecords);
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

	/** Sends a new score to the web server to be added to the leaderboard. Can be called from blueprints. The data is determined by the server when it receives the score record. */
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") void SendScore(int playerScore, FString username, FString difficultyName);

	/**
	 * Query the web server to get the four scores above the player's score and the five scores below the player's score from the web server. 
	 * It is important to understand that this method only executes a GET request to the server and stores the results inside the RequestHandler; it does not
	 * return the scores because it is asynchronous. Can be called from blueprints. The parameter "isSubmitted" specifies whether or not the player's score has
	 * been submitted to the database; if the player's score is not already in the database, it should still be included in the results.
	 * TODO: Rename GetScores() and GetScoreRecords() to be more intuitive. GetScores currently executes a GET request while GetScoreRecords is an accessor.
	 */
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") void GetScores(UPARAM(DisplayName = "Player Score") int playerScore, UPARAM(DisplayName = "Is Submitted") bool isSubmitted);

	/**
	 * Query the top ten scores from the web server, including the player's new score if they are in the top ten and have not saved their score yet. Otherwise similar to GetScores().
	 */ 
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") void GetScoresTop10(UPARAM(DisplayName = "Player Score") int playerScore, UPARAM(DisplayName = "Is Submitted") bool isSubmitted);

	/**
	 * Query the bottom ten scores from the web server, including the player's new score if they are in the bottom ten and have not saved their score yet. Otherwise similar to GetScores().
	 */
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") void GetScoresBottom10(UPARAM(DisplayName = "Player Score") int playerScore, UPARAM(DisplayName = "Is Submitted") bool isSubmitted);

	/**
	 * Access the score records received from the database. This method returns a TArray of FString objects containing the score records for a leaderboard. It is important to understand that this method is asynchronous
	 * and will return an empty list if it is accessed before the server responds to a request. This accessor is useful in a user defined event handler for ReceivedScoresEvent.
	 */
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") TArray<FString> GetScoreRecords();

	/**
	 * Access the player's score index received from the database. This method returns an integer representing the player's standing in the current list of scores. Similar to GetScoreRecords() in all other respects.
	 */
	UFUNCTION(BlueprintCallable, Category = "Switch Functions") int GetPlayerScoreIndex();

	// An event handler that is called when scores are received from the database after internal logic. It can be bound by the containing class or blueprint.
	UPROPERTY(BlueprintAssignable, Category = "Events") FOnReceivedScoreRecords ReceivedScoreRecordsEvent;

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

	UPROPERTY() int playerScoreIndex;

};
