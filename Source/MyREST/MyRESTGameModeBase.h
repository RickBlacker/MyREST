// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Http.h"
#include "Json.h"
#include "APIStruct.h"
#include "MyRESTGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYREST_API AMyRESTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;




private:
	void OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool bConnectedSuccessfully);

	void PostMsg();
	void GetMsg();


	bool WriteAsRawJSON(FString rawJSON );
	bool PopulateCustomStruct(FString rawJSON );
	bool PopulateStructArray(FString rawJSON);

	bool ReadStructure(FPosts& apiStruct, TSharedPtr<FJsonObject> responsObj, FString& jsonStr );

	bool StrctToFJsonObj( FPosts& apiStruct, FString jsonStr );
};
