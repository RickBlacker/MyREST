// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyRESTGameModeBase.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonSerializer.h"
#include "UsersAPI.h"


//https://jsonplaceholder.typicode.com/
//https://jsonplaceholder.typicode.com/posts/1
//https://jsonplaceholder.typicode.com/posts/


void AMyRESTGameModeBase::StartPlay()
{
	Super::StartPlay();


	//GetMsg();
	//PostMsg();

}




void AMyRESTGameModeBase::GetMsg()
{
	FHttpRequestRef req = FHttpModule::Get().CreateRequest();

	req->OnProcessRequestComplete().BindUObject(this, &AMyRESTGameModeBase::OnResponseReceived);
	req->SetURL("https://jsonplaceholder.typicode.com/posts/");
	req->SetVerb("GET");
	req->ProcessRequest();
}



void AMyRESTGameModeBase::PostMsg()
{
	FHttpRequestRef req = FHttpModule::Get().CreateRequest();
	TSharedRef<FJsonObject> reqObj = MakeShared<FJsonObject>();
	
	reqObj->SetStringField("title", "foo");
	reqObj->SetStringField( "", "");

	FString reqstBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&reqstBody);
	FJsonSerializer::Serialize(reqObj, Writer);


	req->OnProcessRequestComplete().BindUObject( this, &AMyRESTGameModeBase::OnResponseReceived);
	req->SetURL("https://jsonplaceholder.typicode.com/posts/1");
	req->SetVerb("POST");
	req->SetHeader("Content-Type", "application/json");
	req->SetContentAsString(reqstBody);
	req->ProcessRequest();
}



void AMyRESTGameModeBase::OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool bConnectedSuccessfully)
{
	FString resp = response->GetContentAsString();

	//WriteAsRawJSON(resp);
	//PopulateCustomStruct(resp);
	PopulateStructArray(resp);
}


/*
Read the JSON string into a UE JSON file and print it out.
*/
bool AMyRESTGameModeBase::WriteAsRawJSON( FString rawJSON )
{
	TSharedPtr<FJsonObject> responseObj;

	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create( rawJSON );

	if (FJsonSerializer::Deserialize(reader, responseObj))
	{
		UE_LOG(LogTemp, Warning, TEXT("RAW UserID = %s"),	*responseObj->GetStringField("userId"));
		UE_LOG(LogTemp, Warning, TEXT("RAW ID = %s"),		*responseObj->GetStringField("id"));
		UE_LOG(LogTemp, Warning, TEXT("RAW Title =  %s"),	*responseObj->GetStringField("title"));
		UE_LOG(LogTemp, Warning, TEXT("RAW Body = %s"),		*responseObj->GetStringField("body"));
	}
	return true;
}



/*
Populate a custom USTRUCT instance, and populate it from the JSON string
*/
bool AMyRESTGameModeBase::PopulateCustomStruct( FString rawJSON )
{
	FPosts apiData;
	TSharedPtr<FJsonObject> responseObj;
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(rawJSON);
	if (FJsonSerializer::Deserialize(reader, responseObj))
	{
		if (FJsonObjectConverter::JsonObjectToUStruct<FPosts>(responseObj.ToSharedRef(), &apiData))
		{
			UE_LOG(LogTemp, Warning, TEXT("STRUCT UserID = %d"),	apiData.UserID);
			UE_LOG(LogTemp, Warning, TEXT("STRUCT ID = %d"),		apiData.TitleID);
			UE_LOG(LogTemp, Warning, TEXT("STRUCT Title =  %s"),	*apiData.Title);
			UE_LOG(LogTemp, Warning, TEXT("STRUCT Body = %s"),		*apiData.Body);

			StrctToFJsonObj(apiData, FString());
		}
	}
	return true;
}




bool AMyRESTGameModeBase::PopulateStructArray(FString rawJSON)
{
	TArray<FPosts> apiDataArray;
	

	if( FJsonObjectConverter::JsonArrayStringToUStruct( rawJSON, &apiDataArray ) )
	{
		for (FPosts d : apiDataArray)
		{
			UE_LOG(LogTemp, Warning, TEXT("=========================================================="));
			UE_LOG(LogTemp, Warning, TEXT("STRUCT ARRAY ITEM UserID = %d"), d.UserID);
			UE_LOG(LogTemp, Warning, TEXT("STRUCT ARRAY ITEM  ID = %d"), d.TitleID);
			UE_LOG(LogTemp, Warning, TEXT("STRUCT ARRAY ITEM  Title =  %s"), *d.Title);
			UE_LOG(LogTemp, Warning, TEXT("STRUCT ARRAY ITEM  Body = %s"), *d.Body);
		}
	}
	return true;
}


//bool AMyRESTGameModeBase::PopulateStructArray(FString rawJSON)
//{
//	TArray<FAPIData> apiDataArray;
//	TSharedPtr<FJsonObject> responseObj;
//	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(rawJSON);
//	if (FJsonSerializer::Deserialize(reader, responseObj))
//	{
//		//if( FJsonObjectConverter::JsonObjectToUStruct<TArray<FAPIData>>(responseObj.ToSharedRef(), &apiDataArray ))
//		if (FJsonObjectConverter::JsonArrayStringToUStruct<TArray<FAPIData>>(responseObj.ToSharedRef(), &apiDataArray))
//		{
//			for (FAPIData d : apiDataArray)
//			{
//				UE_LOG(LogTemp, Warning, TEXT("STRUCT UserID = %d"), d.UserID);
//				UE_LOG(LogTemp, Warning, TEXT("STRUCT ID = %d"), d.TitleID);
//				UE_LOG(LogTemp, Warning, TEXT("STRUCT Title =  %s"), *d.Title);
//				UE_LOG(LogTemp, Warning, TEXT("STRUCT Body = %s"), *d.Body);
//			}
//		}
//	}
//	return true;
//
//}


bool AMyRESTGameModeBase::ReadStructure(FPosts& apiStruct, TSharedPtr<FJsonObject> responsObj, FString& jsonStr)
{
	bool bRet = FJsonObjectConverter::JsonObjectToUStruct<FPosts>(responsObj.ToSharedRef(), &apiStruct);
	return bRet;
}
 


bool AMyRESTGameModeBase::StrctToFJsonObj(FPosts& apiStruct, FString jsonStr)
{
	TSharedPtr<FJsonObject> jsonObj = FJsonObjectConverter::UStructToJsonObject(apiStruct);


	UE_LOG(LogTemp, Warning, TEXT("BACK TO JSON UserID = %s"),	*jsonObj->GetStringField("UserId"));
	UE_LOG(LogTemp, Warning, TEXT("BACK TO JSON ID = %s"),		*jsonObj->GetStringField("TitleId"));
	UE_LOG(LogTemp, Warning, TEXT("BACK TO JSON Title =  %s"),	*jsonObj->GetStringField("Title"));
	UE_LOG(LogTemp, Warning, TEXT("BACK TO JSON Body = %s"),	*jsonObj->GetStringField("Body"));

	return true;
}

