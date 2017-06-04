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

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	// Get the AI controlled tank
	ATank* GetControlledTank() const;

	// Start the game
	void BeginPlay() override;

	// Get the player's tank for AI targeting
	ATank* GetPlayerTank() const;
};
