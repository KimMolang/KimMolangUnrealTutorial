// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

#include "WebConnection.h"


UABGameInstance::UABGameInstance()
{
	//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Constructor Call Start!"));
	AB_LOG(Warning, TEXT("%s"), TEXT("Game Instance Constructor Call Start!"));
	
	m_pWebConnection = CreateDefaultSubobject<UWebConnection>(TEXT("WebConnection"));
	// m_pWebConnection 는 this 의 생성자에서 따로 생성해주는 UObject 이기 때문에
	// Subobject 오브젝트이다. 따라서 저 함수로 생성해야함!
	// 생성자 아닌 곳에서는 NewObject 하면 됌!
	// 인자로 텍스트 넣는 건 서브오브젝트를 관리하기 위한 내부 해시값임

	//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Constructor Call End!"));
	AB_LOG(Warning, TEXT("Game Instance Constructor Call End!"));
}

void UABGameInstance::Init()
{
	Super::Init();
	
	// Verbosity Type : Fatal(강제로 크래시), Error, Warning, Display, Log
	// 강제로 크래시 낼 바에는 check 나 verify 같은 Assertion 매크로를 사용하세요
	// [Assertion 매크로] https://docs.unrealengine.com/latest/INT/Programming/Assertions/
	AB_LOG_CALLONLY(Warning);

	UClass* pUClassInfo_StaticClass = UABGameInstance::StaticClass();
	// 컴파일 타임 부터 이렇게 겟 가능
	UClass* pUClassInfo_GetClass = m_pWebConnection->GetClass();
	// 런타임 부터 이렇게 겟 가능

	if (pUClassInfo_StaticClass == pUClassInfo_GetClass)
	{
		AB_LOG(Warning, TEXT("StaticClass is same wtih GetClass"));
	}

	
	// Find Property
	for (TFieldIterator<UProperty> iter(pUClassInfo_GetClass); iter; ++iter)
	{
		AB_LOG(Warning, TEXT("Field : %s, Type : %s")
			, *iter->GetName(), *iter->GetClass()->GetName() );

		UStrProperty* pStrProp
			= FindField<UStrProperty>(pUClassInfo_GetClass, *iter->GetName());

		if (pStrProp)
		{
			AB_LOG(Warning, TEXT("Value = %s")
				, *pStrProp->GetPropertyValue_InContainer(m_pWebConnection));
		}
	}
	
	// Find Function
	for (const auto& entry : m_pWebConnection->NativeFunctionLookupTable)
	{
		AB_LOG(Warning, TEXT("Function = %s"), *entry.Name.ToString());

		UFunction* pFunc = m_pWebConnection->FindFunctionByName(entry.Name);

		if (pFunc->ParmsSize == 0)
		{
			m_pWebConnection->ProcessEvent(pFunc, NULL);
		}
	}
}