#pragma once

#include "coreminimal.h"
#include "APIStruct.generated.h"

USTRUCT( BlueprintType, Category = "API Data")
struct FPosts
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
	FString Title;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
	FString Body;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
	int32 TitleID;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
	int32 UserID;
};



USTRUCT(BlueprintType, Category = "API Data")
struct FCompany
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
		FString name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
		FString catchPhrase;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
		FString bs;
};




USTRUCT(BlueprintType, Category = "API Data")
struct FGeo
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
		FString lat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
		FString lng;
};



USTRUCT(BlueprintType, Category = "API Data")
struct FAddress
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
		FString street;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
		FString suite;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
		FString city;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
		FString zipcode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
		FGeo geo;

};



USTRUCT(BlueprintType, Category = "API Data")
struct FUserAPIData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
	int32 id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
	FString name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
	FString username;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
	FString email;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
	FString phone;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
	FString website;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
	FAddress address;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "API DATA")
	FCompany company;

};











