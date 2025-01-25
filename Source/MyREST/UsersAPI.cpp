// Fill out your copyright notice in the Description page of Project Settings.


#include "UsersAPI.h"

#include "JsonObjectConverter.h"
#include "Serialization/JsonSerializer.h"


UUsersAPI::UUsersAPI()
{}

void UUsersAPI::GetSingleUser(int32 id)
{
	FHttpRequestRef req = FHttpModule::Get().CreateRequest();

	FString url = "https://jsonplaceholder.typicode.com/users/" + FString::FromInt(id);

	req->OnProcessRequestComplete().BindUObject(this, &UUsersAPI::OnGetOneUserResponseReceived);
	req->SetURL( url );
	req->SetVerb("GET");
	req->ProcessRequest();
}



void UUsersAPI::GetAllUsers()
{
	FHttpRequestRef req = FHttpModule::Get().CreateRequest();

	req->OnProcessRequestComplete().BindUObject(this, &UUsersAPI::OnGetAllUsersResponseReceived);
	req->SetURL("https://jsonplaceholder.typicode.com/users/");
	req->SetVerb("GET");
	req->ProcessRequest();
}


// Single User GET response
void UUsersAPI::OnGetOneUserResponseReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool bConnectedSuccessfully)
{
	FString resp = response->GetContentAsString();
	UE_LOG(LogTemp, Warning, TEXT("SINGLE USER Response = %s"), *resp);
	ConvertJSONStringToStructAndPrint(resp);
}


// POST user update repsonse.
void UUsersAPI::OnPostReplyReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool bConnectedSuccessfully)
{
	FString resp = response->GetContentAsString();
	UE_LOG(LogTemp, Warning, TEXT("POST Response = %s"), *resp);
	ConvertJSONStringToStructAndPrint(resp);
}


// All users GET response
void UUsersAPI::OnGetAllUsersResponseReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool bConnectedSuccessfully)
{
	FString resp = response->GetContentAsString();
	UE_LOG(LogTemp, Warning, TEXT("ALL USERS Response = %s"), *resp);
	ConvertJSONArrayToUserStructAndPrint(resp);

}


// Take a JSON string single user , convert to a FUserAPIData structure and print it.
void UUsersAPI::ConvertJSONStringToStructAndPrint(FString userData)
{
	FUserAPIData ud;

	if(FJsonObjectConverter::JsonObjectStringToUStruct(userData, &ud))
	{
		PrintUser(ud);
	}
}



// Take a JSON string array of users, convert to a TArray of FUserAPIData structures and print it.
void UUsersAPI::ConvertJSONArrayToUserStructAndPrint(FString userData)
{
	TArray<FUserAPIData> apiUsers;

	if (FJsonObjectConverter::JsonArrayStringToUStruct(userData, &apiUsers))
	{
		for (FUserAPIData p : apiUsers)
		{
			PrintUser(p);
		}
	}
}



// Create a new structure, convert it to JSON and send to to the REST api
void UUsersAPI::PostUserData()
{
	FUserAPIData ud;

	ud.email = "fred@bedrockquary.com";
	ud.id = 10;
	ud.name = "Fred Flintstone";
	ud.phone = "555-222-1111";
	ud.username = "FreddyTheRockCrusher";
	ud.website = "www.bedrockquary.com";

	ud.address.city = "Bedrock";
	ud.address.street = "Rocky Road";
	ud.address.geo.lat = "111.222";
	ud.address.geo.lng = "444.555";
	ud.address.suite = "Stone Huts";
	ud.address.zipcode = "123245";

	ud.company.bs = "The Crushers";
	ud.company.catchPhrase = "We Crushem 4U";
	ud.company.name = "Bedrock Quary";


	TSharedPtr<FJsonObject> jsonObj = FJsonObjectConverter::UStructToJsonObject(ud);

	FString postBody;
	FJsonObjectConverter::UStructToJsonObjectString(ud, postBody);
	
	FHttpRequestRef req = FHttpModule::Get().CreateRequest();

	req->OnProcessRequestComplete().BindUObject(this, &UUsersAPI::OnPostReplyReceived);
	req->SetURL("https://jsonplaceholder.typicode.com/users/");
	req->SetVerb("POST");
	req->SetHeader("Content-Type", "application/json");
	req->SetContentAsString(postBody);
	req->ProcessRequest();
}






void UUsersAPI::PrintUser(FUserAPIData& user)
{
	UE_LOG(LogTemp, Warning, TEXT("=========================================================="));
	UE_LOG(LogTemp, Warning, TEXT("ID = %d"), user.id);
	UE_LOG(LogTemp, Warning, TEXT("Name = %s"), *user.name);
	UE_LOG(LogTemp, Warning, TEXT("UserName = %s"), *user.username);
	UE_LOG(LogTemp, Warning, TEXT("Email = %s"), *user.email);
	UE_LOG(LogTemp, Warning, TEXT("Phone = %s"), *user.phone);
	UE_LOG(LogTemp, Warning, TEXT("Website = %s"), *user.website);

	PrintAddress(user.address);
	PrintCompany(user.company);

	UE_LOG(LogTemp, Warning, TEXT(""));
}


void UUsersAPI::PrintAddress(FAddress& address)
{
	UE_LOG(LogTemp, Warning, TEXT("Address.Street = %s"), *address.street);
	UE_LOG(LogTemp, Warning, TEXT("Address.Suite = %s"), *address.suite);
	UE_LOG(LogTemp, Warning, TEXT("Address.City = %s"), *address.city);
	UE_LOG(LogTemp, Warning, TEXT("Address.Zipcode = %s"), *address.zipcode);
	PrintGeo(address.geo);
}


void UUsersAPI::PrintCompany(FCompany& company)
{
	UE_LOG(LogTemp, Warning, TEXT("Company.Name = %s"), *company.name);
	UE_LOG(LogTemp, Warning, TEXT("Company.CatchPhrase = %s"), *company.catchPhrase);
	UE_LOG(LogTemp, Warning, TEXT("Company.BS = %s"), *company.bs);
}


void UUsersAPI::PrintGeo(FGeo& geo)
{
	UE_LOG(LogTemp, Warning, TEXT("Address.Geo.lat = %s"), *geo.lat);
	UE_LOG(LogTemp, Warning, TEXT("Address.Geo.Lng = %s"), *geo.lng);
}
