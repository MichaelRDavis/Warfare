// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WarfareInventoryComponent.generated.h"

class AWarfareInventoryActor;
class AWarfareCharacter;

UCLASS(ClassGroup=(Inventory))
class WARFARE_API UWarfareInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWarfareInventoryComponent();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void InitializeComponent() override;

private:
	UPROPERTY(BlueprintReadOnly, Category=Inventory, meta=(AllowPrivateAccess="true"))
	TObjectPtr<AWarfareCharacter> CharacterOwner;

	UPROPERTY(Replicated, BlueprintReadOnly, Category=Inventory, meta=(AllowPrivateAccess="true"))
	TArray<AWarfareInventoryActor*> Inventory;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	int32 MaxInventorySize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	bool bInitializeOnBeginPlay;

	UFUNCTION(BlueprintPure, Category=Inventory)
	AWarfareCharacter* GetCharacterOwner() const;

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void SetCharacterOwner(AWarfareCharacter* NewOwner);

	UFUNCTION(BlueprintPure, Category=Inventory)
	TArray<AWarfareInventoryActor*> GetInventory() const;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	AWarfareInventoryActor* CreateInventoryActor(TSubclassOf<AWarfareInventoryActor> ActorClass);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	void AddInventoryActor(AWarfareInventoryActor* ActorToAdd);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	void RemoveInventoryActor(AWarfareInventoryActor* ActorToRemove);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	AWarfareInventoryActor* FindInventoryActor(TSubclassOf<AWarfareInventoryActor> ActorClass);
};
