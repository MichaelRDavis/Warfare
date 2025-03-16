// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WarfareCharacter.generated.h"

class UCameraComponent;

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

	/** Handles moving forward/backward */
	void MoveForward(float Value);

	/** Handles strafing movement left and right */
	void MoveRight(float Value);
};
