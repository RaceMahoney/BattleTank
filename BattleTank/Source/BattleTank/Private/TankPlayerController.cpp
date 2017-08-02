// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not possesing a tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing: %s"), *(ControlledTank->GetName()));
	}
	Super::BeginPlay(); //makes sure that begin play is being called
	UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin Play"));
}
	

ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}


