// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WarfarePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UWarfareLoadoutComponent;
class AWarfareLoadoutActor;
class AWarfareCharacter;

UCLASS()
class WARFARE_API AWarfarePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AWarfarePlayerController();

	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Player, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UWarfareLoadoutComponent> PlayerLoadoutComponent;

public:
	FORCEINLINE UWarfareLoadoutComponent* GetPlayerLoadoutComponent() const { return PlayerLoadoutComponent; }

	void GiveLoadout(const TArray<TSubclassOf<AWarfareLoadoutActor>>& Loadout);

private:
	UPROPERTY()
	TObjectPtr<AWarfareCharacter> WarfareCharacter;

	/** Player input MappingConntext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> PlayerMappingContext;

	/** Move input action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look input action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> LookAction;

	/** Jump input action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for look input */
	void Look(const FInputActionValue& Value);

	/** Player pressed jump action */
	void Jump();

	/** Player released jump action */
	void StopJumping();
};
