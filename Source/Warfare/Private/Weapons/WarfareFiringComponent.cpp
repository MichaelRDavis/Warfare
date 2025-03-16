// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/WarfareFiringComponent.h"
#include "Player/WarfarePlayerController.h"

#define FIRING_TRACE ECC_GameTraceChannel1

UWarfareFiringComponent::UWarfareFiringComponent()
{
	CurrentFiringSpread = 0.0f;
}

void UWarfareFiringComponent::SetPlayerController(AWarfarePlayerController* NewController)
{
	PlayerController = NewController;
}

AWarfarePlayerController* UWarfareFiringComponent::GetPlayerController() const
{
	return PlayerController;
}

void UWarfareFiringComponent::FireHitscan()
{
	const int32 RandomSeed = FMath::Rand();
	FRandomStream SpreadRandomStream(RandomSeed);
	const float CurrentSpread = GetCurrentSpread();
	const float ConeHalfAngle = FMath::DegreesToRadians(CurrentSpread * 0.5f);

	const FVector AimDir = GetAdjustedAim();
	const FVector StartTrace = GetFireStartLocation(AimDir);
	const FVector ShootDir = SpreadRandomStream.VRandCone(AimDir, ConeHalfAngle, ConeHalfAngle);
	const FVector EndTrace = StartTrace + ShootDir * HitscanParams.HitscanRange;

	const FHitResult Impact = FiringTrace(StartTrace, EndTrace);

	CurrentFiringSpread = FMath::Min(FiringParams.MaxFiringSpread, CurrentFiringSpread + FiringParams.FiringSpread);
}

float UWarfareFiringComponent::GetCurrentSpread() const
{
	float FinalSpread = FiringParams.Spread + CurrentFiringSpread;
	return FinalSpread;
}

FVector UWarfareFiringComponent::GetAdjustedAim() const
{
	FVector FinalAim = FVector::ZeroVector;

	if (PlayerController)
	{
		FVector CamLoc;
		FRotator CamRot;
		PlayerController->GetPlayerViewPoint(CamLoc, CamRot);
	}

	return FinalAim;
}

FVector UWarfareFiringComponent::GetFireStartLocation(const FVector& AimDir) const
{
	FVector OutStartTrace = FVector::ZeroVector;

	if (PlayerController)
	{
		// Use player's camera
		FRotator CamRot;
		PlayerController->GetPlayerViewPoint(OutStartTrace, CamRot);

		// Adjust trace so there is nothing blocking the ray between the camera and the character, and calculate distance from adjusted start
		OutStartTrace = OutStartTrace + AimDir * ((PlayerController->GetInstigator()->GetActorLocation() - OutStartTrace) | AimDir);
	}

	return OutStartTrace;
}

FHitResult UWarfareFiringComponent::FiringTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	FHitResult Hit(ForceInit);

	if (PlayerController)
	{
		// Perform trace to retrieve hit info
		FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, PlayerController->GetInstigator());
		TraceParams.bReturnPhysicalMaterial = true;

		GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, FIRING_TRACE, TraceParams);
	}

	return Hit;
}
