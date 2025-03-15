// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/WarfareWeapon.h"
#include "Weapons/WarfareFiringComponent.h"

AWarfareWeapon::AWarfareWeapon()
{
	FiringComponent = CreateDefaultSubobject<UWarfareFiringComponent>(TEXT("WeapFiringComp"));
}

EWeaponType AWarfareWeapon::GetWeaponType() const
{
	return WeaponType;
}

void AWarfareWeapon::SetWeaponState(EWeaponState NewWeaponState)
{

}

void AWarfareWeapon::PrimaryUse()
{
	
}

void AWarfareWeapon::SecondaryUse()
{
	
}

void AWarfareWeapon::UpdateState()
{

}
