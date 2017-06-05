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

void UWebConnection::RequestToken()
{
	UE_LOG(WebConnection, Log, TEXT("Request Token Call!"));
}
