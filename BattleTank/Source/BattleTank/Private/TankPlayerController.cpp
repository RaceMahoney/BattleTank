// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay() {

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		//UE_LOG(LogTemp, Warning, TEXT("Player Controller not possesing a tank!"));
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing: %s"), *(ControlledTank->GetName()));
	}
	Super::BeginPlay(); //makes sure that begin play is being called
	//UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin Play"));
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick( DeltaTime );
	//UE_LOG(LogTemp, Warning, TEXT("Player controller ticking"));
	AimTowardsCrosshair();
}
	


ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair(){

	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation)) 
	{ 
		GetControlledTank()->AimAt(HitLocation);
	}

}

//Get world location if linetraace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString());

	//De-project the screen postion of the crosshair to the world direction
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//Line-trace along the LookDirection and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {

	FVector CameraWorldLocation; //To be discarded

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {

	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if(GetWorld() ->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation, 
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}





