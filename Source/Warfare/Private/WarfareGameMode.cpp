// Fill out your copyright notice in the Description page of Project Settings.

#include "WarfareGameMode.h"
#include "WarfarePlayerController.h"

AWarfareGameMode::AWarfareGameMode()
{
	PlayerControllerClass = AWarfarePlayerController::StaticClass();
}

void AWarfareGameMode::SetPlayerDefaults(APawn* PlayerPawn)
{
	Super::SetPlayerDefaults(PlayerPawn);

	AWarfarePlayerController* PlayerController = Cast<AWarfarePlayerController>(PlayerPawn->GetController());
	if (PlayerController)
	{
		if (DefaultInventory.Num() > 0)
		{
			PlayerController->GiveInventory(DefaultInventory);
		}
	}
}