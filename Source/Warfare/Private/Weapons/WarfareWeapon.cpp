// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/WarfareWeapon.h"
#include "Weapons/WarfareFiringComponent.h"
#include "Player/WarfareCharacter.h"

AWarfareWeapon::AWarfareWeapon()
{
	FiringComponent = CreateDefaultSubobject<UWarfareFiringComponent>(TEXT("WeapFiringComp"));
}

void AWarfareWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (WeaponStats.FireRate > 0)
	{
		FireInterval = 60.0f / WeaponStats.FireRate;
	}
}

EWeaponType AWarfareWeapon::GetWeaponType() const
{
	return WeaponType;
}

void AWarfareWeapon::SetWeaponState(EWeaponState NewWeaponState)
{
	const EWeaponState PrevState = CurrentWeaponState;

	if (PrevState == EWeaponState::Firing && NewWeaponState != EWeaponState::Firing)
	{
		EndFiring();
	}

	CurrentWeaponState = NewWeaponState;

	if (PrevState != EWeaponState::Firing && NewWeaponState == EWeaponState::Firing)
	{
		BeginFiring();
	}
}

void AWarfareWeapon::PrimaryUse()
{
	
}

void AWarfareWeapon::SecondaryUse()
{
	
}

void AWarfareWeapon::UpdateState()
{
	EWeaponState NewState = EWeaponState::Idle;

	if (bIsEquipped)
	{
		if (bWantsToFire && CanFire())
		{
			NewState = EWeaponState::Firing;
		}
	}
	else if (bIsEquipping)
	{
		NewState = EWeaponState::Equipping;
	}

	SetWeaponState(NewState);
}

void AWarfareWeapon::Fire()
{
	if (CanFire())
	{
		if (CharacterOwner != nullptr && CharacterOwner->IsLocallyControlled())
		{
			FiringComponent->FireHitscan();
		}
	}
	else if (CharacterOwner != nullptr && CharacterOwner->IsLocallyControlled())
	{

	}

	if (CharacterOwner != nullptr && CharacterOwner->IsLocallyControlled())
	{
		// Local client will notify server 
		if (GetLocalRole() < ROLE_Authority)
		{
			ServerFire();
		}

		// Setup refiring timer
		bIsFiring = CurrentWeaponState == EWeaponState::Firing && FireInterval > 0.0f;
		if (bIsFiring)
		{
			GetWorldTimerManager().SetTimer(FiringTimer, this, &AWarfareWeapon::Fire, FireInterval, false);
		}
	}

	LastFireTime = GetWorld()->GetTimeSeconds();
}

void AWarfareWeapon::StartFire()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		ServerStartFire();
	}

	if (!bWantsToFire)
	{
		bWantsToFire = true;
		UpdateState();
	}
}

void AWarfareWeapon::StopFire()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		ServerStopFire();
	}

	if (bWantsToFire)
	{
		bWantsToFire = false;
		UpdateState();
	}
}

void AWarfareWeapon::BeginFiring()
{
	// Start firing, can be delayed to satisfy FireInterval
	const float GameTime = GetWorld()->GetTimeSeconds();
	if (LastFireTime > 0 && FireInterval > 0.0f && LastFireTime + FireInterval > GameTime)
	{
		GetWorldTimerManager().SetTimer(FiringTimer, this, &AWarfareWeapon::Fire, LastFireTime + FireInterval - GameTime, false);
	}
	else
	{
		Fire();
	}
}

void AWarfareWeapon::EndFiring()
{
	GetWorldTimerManager().ClearTimer(FiringTimer);
	bIsFiring = false;
}

bool AWarfareWeapon::CanFire() const
{
	return CurrentWeaponState == EWeaponState::Idle || CurrentWeaponState == EWeaponState::Firing;
}

void AWarfareWeapon::ServerFire_Implementation()
{
	Fire();
}

bool AWarfareWeapon::ServerFire_Validate()
{
	return true;
}

void AWarfareWeapon::ServerStartFire_Implementation()
{
	StartFire();
}

bool AWarfareWeapon::ServerStartFire_Validate()
{
	return true;
}

void AWarfareWeapon::ServerStopFire_Implementation()
{
	StopFire();
}

bool AWarfareWeapon::ServerStopFire_Validate()
{
	return true;
}