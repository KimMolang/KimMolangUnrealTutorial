// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "WebConnection.generated.h"

//DECLARE_DELEGATE_OneParam(FTokenCompleteSignature, const FString&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTokenCompleteSignature, const FString&, _rToken);

// MULTICAST : Broadcast o / Execute x API 사용해야함
// DYNAMIC : 함수포인터가 아닌 함수 이름을 기반으로 등록하는 방식

/**
 * 
 */
UCLASS()
class WEBSERVICE_API UWebConnection : public UObject
{
	GENERATED_BODY()
	
public:
	UWebConnection();

	UPROPERTY()
	FString		m_fstrHost;
	UPROPERTY()
	FString		m_fstrUrl;

	UFUNCTION()
	void RequestToken(const FString& _rUserID);

	// BlueprintAssignable : 블루프린트에서 해당 델리게이트 검색이 가능하게 하는 키워드
	UPROPERTY(BlueprintAssignable, Category = "WebService")
	FTokenCompleteSignature m_tTokenCompleteDelegate;


	// Serialization
	friend FArchive& operator<<(FArchive& Ar, UWebConnection& WC)
	{
		if (Ar.IsLoading())
		{
			UE_LOG(LogTemp, Warning, TEXT("Archive is Loading State"));
		}
		else if (Ar.IsSaving())
		{
			UE_LOG(LogTemp, Warning, TEXT("Archive is Saving State"));
		}
		else
		{
			return Ar;
		}

		return Ar << WC.m_fstrHost << WC.m_fstrUrl;
	}
};

DECLARE_LOG_CATEGORY_EXTERN(WebConnection, Log, All);