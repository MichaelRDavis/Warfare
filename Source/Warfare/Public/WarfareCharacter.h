// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WarfareCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class WARFARE_API AWarfareCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWarfareCharacter();

private:
	/** Character mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Mesh, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USkeletalMeshComponent> ArmsMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraCommponent;

public:
	/** Returns ArmsMesh subobject */
	FORCEINLINE USkeletalMeshComponent* GetArmsMesh() const { return ArmsMesh; }
	/** Returns FirstPersonCameraComponent subobject */
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraCommponent; }

	// ACharacter interface
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	// End of ACharacter interface

private:
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

	/** Handles moving forward/backward */
	void MoveForward(float Value);

	/** Handles strafing movement left and right */
	void MoveRight(float Value);
};
