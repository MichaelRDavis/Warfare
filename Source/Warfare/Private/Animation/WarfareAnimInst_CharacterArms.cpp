// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/WarfareAnimInst_CharacterArms.h"

UWarfareAnimInst_CharacterArms::UWarfareAnimInst_CharacterArms()
{
	WeaponAnimType = EWeaponAnimType::None;
}

void UWarfareAnimInst_CharacterArms::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (CharacterOwner != nullptr)
	{
		
	}
}