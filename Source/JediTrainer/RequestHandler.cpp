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
	sendScore();	
	Super::BeginPlay();

}

//This will actually send the score up to our database
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


void ARequestHandler::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	//Use bWasSuccessful in order to check if the request went through to the server.
	//If it did, the user should be connected to the Internet.
	//If not, then something must be wrong. 
	//We could do a whole lot better, as something could go wrong that doesn't involve the Internet...

}


// Called every frame
void ARequestHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

