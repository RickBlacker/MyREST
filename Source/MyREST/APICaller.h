// Acts as a very simplistic controller... A wrapper around the class that does the actual calling of the rest api
// Wrapped up by a UE blueprint.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "APICaller.generated.h"

UCLASS()
class MYREST_API AAPICaller : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAPICaller();

	UFUNCTION( BlueprintCallable )
	void GetUsers();

	UFUNCTION(BlueprintCallable)
	void GetSingleUser(int32 id); 
	
	UFUNCTION(BlueprintCallable)
	void PostUser();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
