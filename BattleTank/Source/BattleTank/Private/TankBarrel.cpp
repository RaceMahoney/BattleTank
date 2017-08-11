// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float ReletiveSpeed) {
	//move the barrel the right amount this frame
	ReletiveSpeed = FMath::Clamp<float>(ReletiveSpeed, -1, +1);

	auto ElevationChange = ReletiveSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	//restrict RawNewElevation to the max and min values
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees); 
	SetRelativeRotation(FRotator(Elevation, 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Elevation: %f"), Elevation);
}



