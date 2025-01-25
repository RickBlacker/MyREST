// Acts as a business object for interacting with the backend system. 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Http.h"
#include "Json.h"
#include "APIStruct.h"

#include "UsersAPI.generated.h"

/**
 * 
 */

UCLASS()
class MYREST_API UUsersAPI : public UObject
{
	GENERATED_BODY()
	
public:

	UUsersAPI();

	// Get a single user
	void GetSingleUser(int32 id);
	
	// Get all the users
	void GetAllUsers();

	// Send an update to the rest api for a given user
	void PostUserData();

	void OnGetOneUserResponseReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool bConnectedSuccessfully);

	// Postback when the HTTP request gets data back from rest api to get all users
	void OnGetAllUsersResponseReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool bConnectedSuccessfully);

	// Postback when the HTTP request to post new user data to rest api returns data back
	void OnPostReplyReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool bConnectedSuccessfully);

private:
	void ConvertJSONStringToStructAndPrint(FString userData);
	void ConvertJSONArrayToUserStructAndPrint(FString userData);
	
	void PrintUser(FUserAPIData& user);
	void PrintAddress(FAddress& address);
	void PrintCompany(FCompany& company);
	void PrintGeo(FGeo& geo);

};
