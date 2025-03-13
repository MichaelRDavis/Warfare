// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WarfareLoadoutComponent.generated.h"

class AWarfareLoadoutActor;
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
	UPROPERTY(BlueprintReadOnly, Category=Loadout, meta=(AllowPrivateAccess="true"))
	TObjectPtr<AWarfareCharacter> CharacterOwner;

	UPROPERTY(Replicated, BlueprintReadOnly, Category=Loadout, meta=(AllowPrivateAccess="true"))
	TArray<AWarfareLoadoutActor*> Loadout;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Loadout)
	int32 MaxLoadoutSize;

	UFUNCTION(BlueprintPure, Category=Loadout)
	AWarfareCharacter* GetCharacterOwner() const;

	UFUNCTION(BlueprintCallable, Category=Loadout)
	void SetCharacterOwner(AWarfareCharacter* NewOwner);

	UFUNCTION(BlueprintPure, Category=Loadout)
	TArray<AWarfareLoadoutActor*> GetLoadout() const;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Loadout)
	AWarfareLoadoutActor* CreateLoadoutActor(TSubclassOf<AWarfareLoadoutActor> ActorClass);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Loadout)
	void AddLoadoutActor(AWarfareLoadoutActor* ActorToAdd);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Loadout)
	void RemoveLoadoutActor(AWarfareLoadoutActor* ActorToRemove);

	UFUNCTION(BlueprintCallable, Category=Loadout)
	AWarfareLoadoutActor* FindLoadoutActor(TSubclassOf<AWarfareLoadoutActor> ActorClass);
};
