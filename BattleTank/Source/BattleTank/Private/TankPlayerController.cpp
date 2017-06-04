// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}	
}

ATank* ATankPlayerController::GetControlledTank() const
{	
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector OutHitLocation; // OUT parameter
	if (bGetAimRayHitLocation(OutHitLocation))
	{
		GetControlledTank()->AimAt(OutHitLocation);
	}
}

bool ATankPlayerController::bGetAimRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// De-project the screen position of the cursor to a world direction
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector WorldDirection;
	if (GetLookDirection(ScreenLocation, WorldDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *WorldDirection.ToString()); // # Note format operator for world location #
		GetLookVectorHitLocation(WorldDirection, OutHitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *OutHitLocation.ToString()); // # Note format operator for hit location #
	}
	return true;
}

// Return direction the crosshair is pointing in
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const
{
	FVector WorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		WorldLocation, 
		WorldDirection
	);
}

// Get the location of where the line trace is hitting
bool ATankPlayerController::GetLookVectorHitLocation(FVector WorldDirection, FVector& OutHitLocation) const
{
	// Line trace along look direction and see what we hit
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (WorldDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}
