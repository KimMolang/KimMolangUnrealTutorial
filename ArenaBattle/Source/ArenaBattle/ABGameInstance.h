// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "ABGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public :
	UABGameInstance();
	~UABGameInstance();

	virtual void Init() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="WebService")
	class UWebConnection*	m_pWebConnection;

	UPROPERTY()
	//FStreamableManager*		m_pAssetLoader;
	FStreamableManager		m_tAssetLoader;

	UFUNCTION()
	void RequestTokenComplete(const FString& _rToken);

private :
	void		FindPropertyAndFunction();
	void		FindObject();

private :
	void		HowToUseTheFArchive();
	void		HowToUseTheSerialization();
};
