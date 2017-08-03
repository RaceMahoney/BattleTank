// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	
	// override checks to find this higher in the hiercarchy (in Actor)
	virtual void BeginPlay() override; 

	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	//Start the tank moving the barrel so that the shot hits where the crosshair is in the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLoction) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.333333f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0f;
};
