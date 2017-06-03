// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Tick(float DeltaTime);

	// Get the player/AI controlled tank
	ATank* GetControlledTank() const;

	// Start the game
	void BeginPlay() override;

	// Get the player's tank for AI targeting
	ATank* GetPlayerTank() const;

	// Start moving tank barrel towards crosshair
	void AimTowardsCrosshair();
	
};
