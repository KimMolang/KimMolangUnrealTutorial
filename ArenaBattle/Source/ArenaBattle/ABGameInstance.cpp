// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

#include "WebConnection.h"


UABGameInstance::UABGameInstance()
{
	//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Constructor Call Start!"));
	AB_LOG(Log, TEXT("%s"), TEXT("Game Instance Constructor Call Start!"));
	
	m_pWebConnection = CreateDefaultSubobject<UWebConnection>(TEXT("WebConnection"));
	// m_pWebConnection 는 this 의 생성자에서 따로 생성해주는 UObject 이기 때문에
	// Subobject 오브젝트이다. 따라서 저 함수로 생성해야함!
	// 생성자 아닌 곳에서는 NewObject 하면 됌!
	// 인자로 텍스트 넣는 건 서브오브젝트를 관리하기 위한 내부 해시값임


	//m_pAssetLoader = new FStreamableManager;


	//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Constructor Call End!"));
	AB_LOG(Log, TEXT("Game Instance Constructor Call End!"));
}

UABGameInstance::~UABGameInstance()
{
	//delete m_pAssetLoader;
}

void UABGameInstance::Init()
{
	Super::Init();
	
	// Verbosity Type : Fatal(강제로 크래시), Error, Warning, Display, Log
	// 강제로 크래시 낼 바에는 check 나 verify 같은 Assertion 매크로를 사용하세요
	// [Assertion 매크로] https://docs.unrealengine.com/latest/INT/Programming/Assertions/
	AB_LOG_CALLONLY(Log);

}

void UABGameInstance::FindPropertyAndFunction()
{
	UClass* pUClassInfo_StaticClass = UWebConnection::StaticClass();
	// 컴파일 타임 부터 이렇게 겟 가능
	UClass* pUClassInfo_GetClass = m_pWebConnection->GetClass();
	// 런타임 부터 이렇게 겟 가능

	if (pUClassInfo_StaticClass == pUClassInfo_GetClass)
	{
		AB_LOG(Log, TEXT("StaticClass is same wtih GetClass"));
	}


	// Find Property
	for (TFieldIterator<UProperty> iter(pUClassInfo_GetClass); iter; ++iter)
	{
		AB_LOG(Log, TEXT("Field : %s, Type : %s")
			, *iter->GetName(), *iter->GetClass()->GetName());

		UStrProperty* pStrProp
			= FindField<UStrProperty>(pUClassInfo_GetClass, *iter->GetName());

		if (pStrProp)
		{
			AB_LOG(Log, TEXT("Value = %s")
				, *pStrProp->GetPropertyValue_InContainer(m_pWebConnection));
		}
	}

	// Find Function
	for (const auto& entry : pUClassInfo_GetClass->NativeFunctionLookupTable)
	{
		AB_LOG(Log, TEXT("Function = %s"), *entry.Name.ToString());

		UFunction* pFunc = pUClassInfo_GetClass->FindFunctionByName(entry.Name);

		if (pFunc->ParmsSize == 0)
		{
			m_pWebConnection->ProcessEvent(pFunc, NULL);
		}
	}
}

void UABGameInstance::FindObject()
{
	// Subobjects
	TArray<UObject*> arrDefaultSubobjects;
	GetDefaultSubobjects(arrDefaultSubobjects);

	for (const auto& entry : arrDefaultSubobjects)
	{
		AB_LOG(Log, TEXT("arrDefaultSubobjects : %s"), *entry->GetClass()->GetName());
		AB_LOG(Log, TEXT("Outer of arrDefaultSubobjects: %s"), *entry->GetOuter()->GetClass()->GetName());
	}

	// 월드에 있는 모든 액터
	UWorld* pCurWorld = GetWorld();
	for (const auto& entry : FActorRange(pCurWorld))
	{
		AB_LOG(Warning, TEXT("Actor : %s"), *entry->GetName());

		TArray<UObject*> arrComponents;
		entry->GetDefaultSubobjects(arrComponents);

		for (const auto& entry_components : arrComponents)
		{
			AB_LOG(Warning, TEXT(" -- Component : %s"), *entry_components->GetName());
		}
	}

	// 특정 조건 액터만 탐색
	// AStaticMeshActor : 스테이틱 메쉬만
	for (TActorIterator<AStaticMeshActor> iter(pCurWorld); iter; ++iter)
	{
		AB_LOG(Warning, TEXT("StaticMesh Actor : %s"), *iter->GetName());
	}

	// UWebConnection 객체 찾기
	UWebConnection* pWebConnection_NewObject = NewObject<UWebConnection>(this);
	AB_LOG(Log, TEXT("Outer of m_pWebConnection_NewObject: %s")
		, *pWebConnection_NewObject->GetOuter()->GetClass()->GetName());

	m_pWebConnection->m_fstrHost = TEXT("localhost");
	pWebConnection_NewObject->m_fstrHost = TEXT("127.0.0.1");

	for (TObjectIterator<UWebConnection> iter; iter; ++iter)
	{
		UWebConnection* pWebConnection = *iter;
		AB_LOG(Warning, TEXT("WebConnction Name : %s"), *pWebConnection->GetName());
		AB_LOG(Warning, TEXT("WebConnction Outer : %s"), *pWebConnection->GetOuter()->GetClass()->GetName());
		AB_LOG(Warning, TEXT("WebConnction Object Host : %s"), *pWebConnection->m_fstrHost);
	}

	DeleteObject(pWebConnection_NewObject);
}