// Fill out your copyright notice in the Description page of Project Settings.

#include "JediTrainer.h"
#include "RequestHandler.h"

/**
Tutorials followed:
+ https://wiki.unrealengine.com/UE4.10_How_To_Make_HTTP_GET_Request_in_C%2B%2B   (Recommend looking at this one first for adding dependencies to the Build file)
+ http://www.wraiyth.com/?p=198  (Doing JSON stuff)
+ https://forums.unrealengine.com/showthread.php?66967-How-to-make-an-HTTP-Request-from-Unreal (Example of POST request)
*/

// Sets default values
ARequestHandler::ARequestHandler(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Http = &FHttpModule::Get();
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARequestHandler::BeginPlay()
{
	//sendScore();	
	Super::BeginPlay();

}

//This will actually send the score up to our database
//Need these parameters: name, score, difficulty
void ARequestHandler::sendScore() {
	//Create the JSON object
	TSharedPtr<FJsonObject> json = MakeShareable(new FJsonObject);
	json->SetStringField("id", "54");
	json->SetStringField("name", "Mikey DAT BOI");
	json->SetStringField("score", "88");
	json->SetStringField("difficulty", "Padawan");


	//This serializes the JSON into a String that you can pass to an HTTP request.
	FString output;
	TSharedRef< TJsonWriter<> > writer = TJsonWriterFactory<>::Create(&output);
	FJsonSerializer::Serialize(json.ToSharedRef(), writer);

	//This creates the POST request and sends the data off.
	TSharedRef<IHttpRequest> request = Http->CreateRequest();
	request->OnProcessRequestComplete().BindUObject(this, &ARequestHandler::OnResponseReceived);
	request->SetHeader("Content-Type", "application/json");
	request->SetURL("http://jeditrainer.herokuapp.com/score");
	request->SetVerb("POST");
	//Send the converted JSON object
	request->SetContentAsString(output);
	request->ProcessRequest();

}

void ARequestHandler::GetScores() {	
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ARequestHandler::OnResponseReceived);
	//This is the url on which to process the request
	Request->SetURL("http://jeditrainer.herokuapp.com/scores");
	Request->SetVerb("GET");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	if (Request->ProcessRequest()) {
		UE_LOG(TraceLog, Warning, TEXT("Request processed successfully."));
	}
	else {
		UE_LOG(TraceLog, Warning, TEXT("WARNING: Request could not be processed."));
	}
}

TArray<FString> ARequestHandler::GetScoreRecords() {
	return scoreRecords;
}

void ARequestHandler::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	//Use bWasSuccessful in order to check if the request went through to the server.
	//If it did, the user should be connected to the Internet.
	//If not, then something must be wrong. 
	//We could do a whole lot better, as something could go wrong that doesn't involve the Internet...
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonValue> JsonObject;;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		// This answer on Unreal answers was helpful while I was writing this section.
		// https://answers.unrealengine.com/questions/271705/how-to-parse-json-array.html

		// Assume that the JSON Object we are receiving is an array containing records.
		TArray<TSharedPtr<FJsonValue>> jsonArray = JsonObject->AsArray();
		
		// Loop through each object in the JSON array.
		for (int i = 0; i < jsonArray.Num(); i++) {
			TSharedPtr<FJsonObject> object = jsonArray[i]->AsObject();
			FString name = object->GetStringField("name");
			int score = object->GetIntegerField("score");
			FString scoreRecord = name + "\t-\t" + FString::FromInt(score);
			this->scoreRecords.Emplace(scoreRecord);
			UE_LOG(TraceLog, Warning, TEXT("Value emplaced."));
		}

		ReceivedScoreRecordsEvent.Broadcast();

	}
	else {
		UE_LOG(TraceLog, Warning, TEXT("WARNING: Could not deserialize JSON content."));
	}

}


// Called every frame
void ARequestHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

