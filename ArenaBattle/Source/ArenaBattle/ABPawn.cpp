// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"

#include "ABGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

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
	m_pMovement		= CreateDefaultSubobject<UFloatingPawnMovement>("Movement");

	m_pMesh->SetupAttachment(m_pBody);
	m_pArrow->SetupAttachment(m_pBody);
	m_pSpringArm->SetupAttachment(m_pBody);
	m_pCamera->SetupAttachment(m_pSpringArm);

	m_pBody->SetCapsuleSize(34.0f, 88.0f);
	m_pMesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.f, 0.0f));

	// Set Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Warrior(TEXT(
		"SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));

	m_pMesh->SetSkeletalMesh(SK_Warrior.Object);

	// Set Camera
	m_pSpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	m_pSpringArm->TargetArmLength	= 650.0f;
	m_pSpringArm->bInheritPitch		= false;
	m_pSpringArm->bInheritYaw		= false;
	m_pSpringArm->bInheritRoll		= false;

	// Set HP
	m_fCurrentHP	= MAX_HP;


	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	

	m_fCurrentHP = MAX_HP;

	m_iCharMeshType						= FMath::RandRange(0, m_arrCharacterAssets.Num() - 1);
	UABGameInstance* pABGameInstance	= Cast<UABGameInstance>(GetGameInstance());
	
	if(pABGameInstance == nullptr)
		return;


	//TAssetPtr<USkeletalMesh> pCharacterMesh = Cast<USkeletalMesh>(
	//	pABGameInstance->m_tAssetLoader.SynchronousLoad(m_arrCharacterAssets[iRandomIndex]) );

	//if(pCharacterMesh == nullptr)
	//	return;


	//m_pMesh->SetSkeletalMesh(pCharacterMesh.Get());


	pABGameInstance->m_tAssetLoader.RequestAsyncLoad( m_arrCharacterAssets[m_iCharMeshType]
													, FStreamableDelegate::CreateUObject(this, &AABPawn::CharacterMeshDeferred) );
}

// Called every frame
void AABPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector vecInputVal = FVector(m_fCurUpDownVal, m_fCurLeftRightVal, 0.0F);
	if (vecInputVal.SizeSquared() > 0.0F)
	{
		FRotator vecTargetRotation = UKismetMathLibrary::MakeRotFromX(vecInputVal);
		SetActorRotation(vecTargetRotation);
		AddMovementInput(GetActorForwardVector());
	}
}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("LeftRight", this, &AABPawn::SetCurLeftRifgtVal);
	InputComponent->BindAxis("UpDown", this, &AABPawn::SetCurUpDownVal);
}

void AABPawn::CharacterMeshDeferred()
{
	AB_LOG_CALLONLY(Warning);

	TAssetPtr<USkeletalMesh> pNewCharacter(m_arrCharacterAssets[m_iCharMeshType]);

	if (pNewCharacter)
	{
		m_pMesh->SetSkeletalMesh(pNewCharacter.Get());
	}
}

