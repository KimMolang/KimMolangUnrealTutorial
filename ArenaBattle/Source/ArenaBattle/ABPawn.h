// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "ABPawn.generated.h"

UCLASS(config=Game)
class ARENABATTLE_API AABPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AABPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Collision")
	class UCapsuleComponent*		m_pBody;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Visual")
	class USkeletalMeshComponent*	m_pMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Helper")
	class UArrowComponent*			m_pArrow;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
	class USpringArmComponent*		m_pSpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
	class UCameraComponent*			m_pCamera;

	UPROPERTY(config, BlueprintReadWrite, EditDefaultsOnly, Category = "Stat")
	float		MAX_HP;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Stat")
	float		m_fCurrentHP;


private :
	UPROPERTY(config)
	TArray<FStringAssetReference>	m_arrCharacterAssets;	
};
