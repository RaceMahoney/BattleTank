// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay() {

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller cannot find player tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found player: %s"), *(PlayerTank->GetName()));
	}
	Super::BeginPlay(); //makes sure that begin play is being called
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
}


ATank* ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {

	auto PlayerPawn = GetWorld()->GetFirstPlayerController() -> GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

