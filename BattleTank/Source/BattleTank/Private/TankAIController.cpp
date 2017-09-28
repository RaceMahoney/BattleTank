

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();



	if (!ensure(PlayerTank && ControlledTank)) { return; }

		//Move Towards Player
		MoveToActor(PlayerTank, AcceptenceRadius); //TODO check radius in cm

		//Aim towards player
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) { return; }
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		AimingComponent->Fire(); 
	
}



