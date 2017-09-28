// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float ReletiveSpeed) {
	//move the turret the right amount this frame
	ReletiveSpeed = FMath::Clamp<float>(ReletiveSpeed, -1, +1);

	auto RotationChange = ReletiveSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));

}


