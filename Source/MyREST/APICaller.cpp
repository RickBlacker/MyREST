// Fill out your copyright notice in the Description page of Project Settings.


#include "APICaller.h"
#include "UsersAPI.h"
// Sets default values
AAPICaller::AAPICaller()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AAPICaller::GetUsers()
{
	UUsersAPI* uapi = NewObject<UUsersAPI>();
	uapi->GetAllUsers();
	uapi = nullptr;
}


void AAPICaller::PostUser()
{
	UUsersAPI* uapi = NewObject<UUsersAPI>();
	uapi->PostUserData();
	uapi = nullptr;
}


void AAPICaller::GetSingleUser(int32 id)
{
	UUsersAPI* uapi = NewObject<UUsersAPI>();
	uapi->GetSingleUser(id);
	uapi = nullptr;
}



// Called when the game starts or when spawned
void AAPICaller::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AAPICaller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

