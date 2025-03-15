// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/WarfareAnimInst_CharacterArms.h"
#include "Player/WarfarePlayerController.h"
#include "Loadout/WarfareLoadoutComponent.h"
#include "Weapons/WarfareWeapon.h"

UWarfareAnimInst_CharacterArms::UWarfareAnimInst_CharacterArms()
{
	
}

void UWarfareAnimInst_CharacterArms::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UWarfareAnimInst_CharacterArms::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (CharacterOwner != nullptr)
	{
		if (PlayerController)
		{
			UWarfareLoadoutComponent* Loadout = PlayerController->GetPlayerLoadoutComponent();
			if (Loadout->GetWeapon() != nullptr)
			{
				Weapon = Loadout->GetWeapon();
			}
		}

		if (Weapon)
		{
			EWeaponType WeapType = Weapon->GetWeaponType();
			if (WeapType == EWeaponType::Handgun)
			{
				WeaponAnimType = EWeaponAnimType::Handgun;
			}
			else if (WeapType == EWeaponType::AssaultRifle)
			{
				WeaponAnimType = EWeaponAnimType::AssaultRifle;
			}
		}
	}
}