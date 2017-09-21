#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/*
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// override checks to find this higher in the hiercarchy (in Actor)
	virtual void BeginPlay() override; 

	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	
	
	//Start the tank moving the barrel so that the shot hits where the crosshair is in the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLoction) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.333333f;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0f;
};
