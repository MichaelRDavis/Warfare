// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarfareLoadoutActor.generated.h"

class AWarfareCharacter;

USTRUCT(BlueprintType)
struct FLoadoutActorAnimation
{
	GENERATED_USTRUCT_BODY()

	/** Animation player on first person view */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animation)
	TObjectPtr<UAnimMontage> Anim1P;

	/** Animation player on third person view */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animation)
	TObjectPtr<UAnimMontage> Anim3P;
};

UCLASS(Abstract, Blueprintable, Notplaceable)
class WARFARE_API AWarfareLoadoutActor : public AActor
{
	GENERATED_BODY()
	
public:
	AWarfareLoadoutActor();

private:
	/** Loadout actor mesh: 1st person view */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Mesh, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	/** Loadout actor mesh: 3rd person view */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Mesh, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USkeletalMeshComponent> Mesh3P;

public:
	/** Returns Mesh1P subobject */
	FORCEINLINE USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns Mesh3P subobject */
	FORCEINLINE USkeletalMeshComponent* GetMesh3P() const { return Mesh3P; }

protected:
	UPROPERTY(BlueprintReadOnly, Category=Loadout)
	TObjectPtr<AWarfareCharacter> CharacterOwner;

public:
	/** Gets character owner */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category=Loadout)
	AWarfareCharacter* GetCharacterOwner() const;

	/** Called when this loadout actor has been added to loadout */
	virtual void AddToLoadout(AWarfareCharacter* NewOwner);

	/** Called when this loadout actor has been removed from loadout */
	virtual void RemoveFromLoadout();

protected:
	/** Name of bone/socket for loadout actor attachment */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Loadout)
	FName HandsAttachSocket;

	/** Equip animations */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Loadout)
	FLoadoutActorAnimation EquipAnimation;

	/** Equip sounds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Loadout)
	TArray<USoundBase*> EquipSounds;

	/** Last time this loadout actor was switched to */
	UPROPERTY(BlueprintReadOnly, Category=Loadout)
	float EquipStartedTime;

	/** Time duration of loadout actor equip */
	UPROPERTY(BlueprintReadOnly, Category=Loadout)
	float EquipDuration;

	/** If true this loadout actor can be equipped by the owning character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Loadout)
	bool bIsHoldable;

	/** If true loadout actor is being equipped */
	UPROPERTY(BlueprintReadOnly, Category=Loadout)
	bool bIsEquipping;

	/** If true loadout actor is equipped */
	UPROPERTY(BlueprintReadOnly, Category=Loadout)
	bool bIsEquipped;

private:
	FTimerHandle OnEquippedTimer;

protected:
	/** Attaches weapon mesh to character */
	virtual void AttachToOwner();

	/** Detaches weapon mesh from character */
	virtual void DetachFromOwner();

public:
	/** Loadout actor is being equipped by owner character */
	virtual void OnEquip();

	/** Loadout actor is now equipped by owner character */
	virtual void OnEquipped();

	/** Loadout actor is unequipped by owner character */
	virtual void OnUnEquip();

	/** Returns last time this load actor was switched to */
	UFUNCTION(BlueprintPure, Category=Loadout)
	float GetEquipStartedTime() const;

	/** Gets duration of equipping loadout actor */
	UFUNCTION(BlueprintPure, Category=Loadout)
	float GetEquipDuration() const;

	/** Check if loadout actor is equipped */
	UFUNCTION(BlueprintPure, Category=Loadout)
	bool IsEquipped() const;

	/** Check if mesh is already attached to character owner */
	UFUNCTION(BlueprintPure, Category=Loadout)
	bool IsAttached() const;

	/** Called on primary use, called from owning character */
	virtual void PrimaryUse();

	/** Called on secondary use, called from owning character */
	virtual void SecondaryUse();

	/** Called to set loadout actor state */
	virtual void SetState();

	/** Called to update state of loadout actor */
	virtual void UpdateState();
};
