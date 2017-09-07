// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override; // override checks to find this higher in the hiercarchy (in Actor)

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//how close the tank can get to the player
	float AcceptenceRadius = 3000;

};
