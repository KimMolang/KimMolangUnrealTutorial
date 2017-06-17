// Fill out your copyright notice in the Description page of Project Settings.

#include "WebService.h"
#include "WebConnection.h"

DEFINE_LOG_CATEGORY(WebConnection);


UWebConnection::UWebConnection()
{
	UE_LOG(LogClass, Log, TEXT("%s"), TEXT("WebConnection Constructor Call!"));

	m_fstrHost	= TEXT("localhost:8000");
	m_fstrUrl	= TEXT("/");
}

void UWebConnection::RequestToken(const FString& _rUserID)
{
	UE_LOG(WebConnection, Log, TEXT("Request Token Call!"));
	//m_tTokenCompleteDelegate.ExecuteIfBound(TEXT(
	//	"0LCJydGkiOiI2a3NjVE9pTUNESVZWM05qVTIyUnlTIn0.VJyMOicM"));
	m_tTokenCompleteDelegate.Broadcast(TEXT(
		"0LCJydGkiOiI2a3NjVE9pTUNESVZWM05qVTIyUnlTIn0.VJyMOicM"));
	// ��������Ʈ�� ��ϵǾ� �ִ� �Լ��� ���ϸ� �Ķ��Ÿ�� �Ѱ��ش�.
}
