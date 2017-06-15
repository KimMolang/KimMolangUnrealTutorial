// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"

#include "ABGameInstance.h"

#include "ABPawn.h"


// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = m_pBody	= CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	m_pMesh			= CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	m_pArrow		= CreateDefaultSubobject<UArrowComponent>("Arrow");
	m_pSpringArm	= CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	m_pCamera		= CreateDefaultSubobject<UCameraComponent>("Camera");

	m_pMesh->SetupAttachment(m_pBody);
	m_pArrow->SetupAttachment(m_pBody);
	m_pSpringArm->SetupAttachment(m_pBody);
	m_pCamera->SetupAttachment(m_pSpringArm);

	m_pBody->SetCapsuleSize(34.0f, 88.0f);
	m_pMesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Warrior(TEXT(
		"SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));

	m_pMesh->SetSkeletalMesh(SK_Warrior.Object);

	m_pSpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	m_pSpringArm->TargetArmLength = 650.0f;

	m_fCurrentHP	= MAX_HP;
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	

	m_fCurrentHP = MAX_HP;

	int32 iRandomIndex					= FMath::RandRange(0, m_arrCharacterAssets.Num() - 1);
	UABGameInstance* pABGameInstance	= Cast<UABGameInstance>(GetGameInstance());
	
	if(pABGameInstance == nullptr)
		return;


	TAssetPtr<USkeletalMesh> pCharacterMesh = Cast<USkeletalMesh>(
		pABGameInstance->m_tAssetLoader.SynchronousLoad(m_arrCharacterAssets[iRandomIndex]) );

	if(pCharacterMesh == nullptr)
		return;


	m_pMesh->SetSkeletalMesh(pCharacterMesh.Get());
}

// Called every frame
void AABPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

