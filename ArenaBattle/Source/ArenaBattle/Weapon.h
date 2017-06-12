// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class USkeletalMeshComponent;

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


UCLASS()
class ARENABATTLE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


public :
	UFUNCTION(BlueprintCallable, Category="Weapon|Stat")
	USkeletalMeshComponent* GetWeapon()	{ return m_pWeapon; }


public :
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "DAMAGE")
		float	DAMAGE_BASE;
private :
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent*	m_pWeapon;
};
