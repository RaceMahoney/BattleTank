

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"



void UTankAimingComponent::SetBarrelRefrence(UTankBarrel* BarrelToSet) {
	if (!BarrelToSet) { return;}
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretRefrence(UTankTurret* TurretToSet) {
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}


UTankAimingComponent::UTankAimingComponent() {
//	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {

	if (!Barrel) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("no barrel found"));  
		return; 
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the outlaunchvelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if (bHaveAimSolution) 
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	
	//work out difference between current barrel rotation and Aim Direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();		//roll, pich and yor of the barrel at the moment
	auto AimAsRotator = AimDirection.Rotation();					//where the barrel is aiming as a rotation
	auto DeltaRotator = AimAsRotator - BarrelRotator;				//the difference in rotation this frame
	
	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->Rotate(DeltaRotator.Yaw);
	
}


