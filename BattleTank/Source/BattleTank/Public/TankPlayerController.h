// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be included last

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Get the player controlled tank
	ATank* GetControlledTank() const;

	// Start the game
	void BeginPlay() override;

	// Start moving tank barrel towards crosshair
	void AimTowardsCrosshair();

	// Return true if the aim linetrace hits a tank
	bool bGetAimRayHitLocation(FVector& OutHitLocation) const;

	// Return direction the crosshair is pointing in
	bool GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const;

	// Get the location of where the line trace is hitting
	bool GetLookVectorHitLocation(FVector WorldDirection, FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
