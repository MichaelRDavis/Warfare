// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WarfareLoadoutComponent.generated.h"

class AWarfareLoadoutActor;
class AWarfareWeapon;
class AWarfareCharacter;

UCLASS(ClassGroup=(Loadout))
class WARFARE_API UWarfareLoadoutComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWarfareLoadoutComponent();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void InitializeComponent() override;

private:
	/** Owner that owns this loadout */
	UPROPERTY(BlueprintReadOnly, Category=Loadout, meta=(AllowPrivateAccess="true"))
	TObjectPtr<AWarfareCharacter> CharacterOwner;

	/** List of loadout items */
	UPROPERTY(Replicated, BlueprintReadOnly, Category=Loadout, meta=(AllowPrivateAccess="true"))
	TArray<AWarfareLoadoutActor*> Loadout;

	/** Currently held weapon */
	UPROPERTY(Replicated, BlueprintReadOnly, ReplicatedUsing=OnRep_SwitchWeapon, meta=(AllowPrivateAccess="true"))
	TObjectPtr<AWarfareWeapon> Weapon;

public:
	/** Maximum number of items allowed in loadout */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Loadout)
	int32 MaxLoadoutSize;

	/** Returns owning character */
	UFUNCTION(BlueprintPure, Category=Loadout)
	AWarfareCharacter* GetCharacterOwner() const;

	/** Sets character owner */
	UFUNCTION(BlueprintCallable, Category=Loadout)
	void SetCharacterOwner(AWarfareCharacter* NewOwner);

	/** Get loadout items */
	UFUNCTION(BlueprintPure, Category=Loadout)
	TArray<AWarfareLoadoutActor*> GetLoadout() const;

	/** Spawns a loadout item */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Loadout)
	AWarfareLoadoutActor* CreateLoadoutActor(TSubclassOf<AWarfareLoadoutActor> ActorClass);

	/** Adds a loadout item to the loadout */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Loadout)
	void AddLoadoutActor(AWarfareLoadoutActor* ActorToAdd);

	/** Removes a loadout item from the loadout */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Loadout)
	void RemoveLoadoutActor(AWarfareLoadoutActor* ActorToRemove);
	
	/** Finds a loadout item, returns found loadout item */
	UFUNCTION(BlueprintCallable, Category=Loadout)
	AWarfareLoadoutActor* FindLoadoutActorByClass(TSubclassOf<AWarfareLoadoutActor> ActorClass);

	/** Finds a loadout item, returns true if found */
	UFUNCTION(BlueprintCallable, Category=Loadout)
	bool FindLoadoutActor(TSubclassOf<AWarfareLoadoutActor> ActorClass);

	/** Destroy loadout */
	UFUNCTION(BlueprintCallable, Category=Loadout)
	void DestroyLoadout();

	/** Switches current weapon */
	UFUNCTION(BlueprintCallable, Category=Loadout)
	void SwitchWeapon(AWarfareWeapon* NewWeapon, AWarfareWeapon* LastWeapon = nullptr);

	/** Switch weapon */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSwitchWeapon(AWarfareWeapon* NewWeapon);
	void ServerSwitchWeapon_Implementation(AWarfareWeapon* NewWeapon);
	bool ServerSwitchWeapon_Validate(AWarfareWeapon* NewWeapon);

	/** Rep handler for switching weapon */
	UFUNCTION()
	void OnRep_SwitchWeapon(AWarfareWeapon* LastWeapon);

	/** Get currently held weapon */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category=Loadout)
	AWarfareWeapon* GetWeapon() const;
};
