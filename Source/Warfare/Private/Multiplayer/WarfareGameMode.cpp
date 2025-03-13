// Fill out your copyright notice in the Description page of Project Settings.

#include "Multiplayer/WarfareGameMode.h"
#include "Player/WarfarePlayerController.h"

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
		if (DefaultLoadoutClasses.Num() > 0)
		{
			PlayerController->GiveLoadout(DefaultLoadoutClasses);
		}
	}
}