// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

#include "WebConnection.h"


UABGameInstance::UABGameInstance()
{
	//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Constructor Call Start!"));
	AB_LOG(Warning, TEXT("%s"), TEXT("Game Instance Constructor Call Start!"));
	
	m_pWebConnection = CreateDefaultSubobject<UWebConnection>(TEXT("WebConnection"));
	// m_pWebConnection �� this �� �����ڿ��� ���� �������ִ� UObject �̱� ������
	// Subobject ������Ʈ�̴�. ���� �� �Լ��� �����ؾ���!
	// ������ �ƴ� �������� NewObject �ϸ� ��!
	// ���ڷ� �ؽ�Ʈ �ִ� �� ���������Ʈ�� �����ϱ� ���� ���� �ؽð���

	//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Constructor Call End!"));
	AB_LOG(Warning, TEXT("Game Instance Constructor Call End!"));
}

void UABGameInstance::Init()
{
	Super::Init();
	
	// Verbosity Type : Fatal(������ ũ����), Error, Warning, Display, Log
	// ������ ũ���� �� �ٿ��� check �� verify ���� Assertion ��ũ�θ� ����ϼ���
	// [Assertion ��ũ��] https://docs.unrealengine.com/latest/INT/Programming/Assertions/
	AB_LOG_CALLONLY(Warning);

	UClass* pUClassInfo_StaticClass = UABGameInstance::StaticClass();
	// ������ Ÿ�� ���� �̷��� �� ����
	UClass* pUClassInfo_GetClass = m_pWebConnection->GetClass();
	// ��Ÿ�� ���� �̷��� �� ����

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