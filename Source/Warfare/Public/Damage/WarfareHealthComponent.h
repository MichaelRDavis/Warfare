// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DamageEvents.h"
#include "Components/ActorComponent.h"
#include "WarfareHealthComponent.generated.h"

/** Replicated hit information */
USTRUCT(BlueprintType)
struct FTakeHitInfo
{
	GENERATED_USTRUCT_BODY()

	/** Damage applied on hit */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=HitInfo)
	float Damage;

	/** Hit damage type */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=HitInfo)
	TSubclassOf<UDamageType> DamageType;

	/** Instigator of hit */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=HitInfo)
	TWeakObjectPtr<APawn> PawnInstigator;

	/** Actor responsible for causing hit */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=HitInfo)
	TWeakObjectPtr<AActor> DamageCauser;

	/** ID of damage event type */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=HitInfo)
	int32 DamageEventID;

	/** If true this hit destroyed the actor hit */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=HitInfo)
	bool bPendingDestroy;

private:
	/** Rolling hit counter of same damage type taken */
	UPROPERTY()
	uint8 HitCounter;

	UPROPERTY()
	FDamageEvent GeneralDamageEvent;
	UPROPERTY()
	FPointDamageEvent PointDamageEvent;
	UPROPERTY()
	FRadialDamageEvent RadialDamageEvent;

public:
	FTakeHitInfo();

	FDamageEvent& GetDamageEvent();
	void SetDamageEvent(const FDamageEvent& DamageEvent);
	void AddHit();
};

UCLASS(ClassGroup=(Health))
class WARFARE_API UWarfareHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWarfareHealthComponent();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void BeginPlay() override;

protected:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category=Health)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Health)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Health)
	bool bIsDestroyed;

	UPROPERTY(Replicated, ReplicatedUsing=OnRep_TakeHit, BlueprintReadOnly, Category=Health)
	FTakeHitInfo TakeHitInfo;

	UPROPERTY()
	float LastTakeHitTimeTimeout;

public:
	UFUNCTION()
	virtual void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION()
	virtual void Destroy();

	UFUNCTION()
	virtual void TakeHit(float Damage, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser, bool bDestroyed);

	UFUNCTION()
	void OnRep_TakeHit();
};
