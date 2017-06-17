// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

#include "WebConnection.h"
//#include <iostrem>
#include <memory>


UABGameInstance::UABGameInstance()
{
	//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Constructor Call Start!"));
	AB_LOG(Log, TEXT("%s"), TEXT("Game Instance Constructor Call Start!"));
	
	m_pWebConnection = CreateDefaultSubobject<UWebConnection>(TEXT("WebConnection"));
	// m_pWebConnection �� this �� �����ڿ��� ���� �������ִ� UObject �̱� ������
	// Subobject ������Ʈ�̴�. ���� �� �Լ��� �����ؾ���!
	// ������ �ƴ� �������� NewObject �ϸ� ��!
	// ���ڷ� �ؽ�Ʈ �ִ� �� ���������Ʈ�� �����ϱ� ���� ���� �ؽð���


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
	
	// Verbosity Type : Fatal(������ ũ����), Error, Warning, Display, Log
	// ������ ũ���� �� �ٿ��� check �� verify ���� Assertion ��ũ�θ� ����ϼ���
	// [Assertion ��ũ��] https://docs.unrealengine.com/latest/INT/Programming/Assertions/
	AB_LOG_CALLONLY(Log);


	//m_pWebConnection->m_tTokenCompleteDelegate.BindUObject(this, &UABGameInstance::RequestTokenComplete);
	m_pWebConnection->m_tTokenCompleteDelegate.AddDynamic(this, &UABGameInstance::RequestTokenComplete);
	// ��������Ʈ���� �Լ��� ����� �ش�.
	m_pWebConnection->RequestToken(TEXT("destiny")); // ���̵� ����


	HowToUseTheSerialization();
}

void UABGameInstance::FindPropertyAndFunction()
{
	UClass* pUClassInfo_StaticClass = UWebConnection::StaticClass();
	// ������ Ÿ�� ���� �̷��� �� ����
	UClass* pUClassInfo_GetClass = m_pWebConnection->GetClass();
	// ��Ÿ�� ���� �̷��� �� ����

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

void UABGameInstance::RequestTokenComplete(const FString& _rToken)
{
	AB_LOG(Warning, TEXT("Token : %s"), *_rToken);
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

	// ���忡 �ִ� ��� ����
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

	// Ư�� ���� ���͸� Ž��
	// AStaticMeshActor : ������ƽ �޽���
	for (TActorIterator<AStaticMeshActor> iter(pCurWorld); iter; ++iter)
	{
		AB_LOG(Warning, TEXT("StaticMesh Actor : %s"), *iter->GetName());
	}

	// UWebConnection ��ü ã��
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

void UABGameInstance::HowToUseTheFArchive()
{
	// WebConnection.txt �� ����
	//std::unique_ptr<UWebConnection> pTmpWebConnection = NewObject<UWebConnection>(this);
	//TUniquePtr<UWebConnection> pTmpWebConnection = NewObject<UWebConnection>(this);
	UWebConnection* pTmpWebConnection = NewObject<UWebConnection>(this);
	pTmpWebConnection->m_fstrHost = TEXT("127.0.0.7");
	pTmpWebConnection->m_fstrUrl = TEXT("/");

	// FPaths::GameSavedDir() ������Ʈ��\Saved ���
	FString fstrFullPath = FString::Printf(TEXT("%s%s"), *FPaths::GameSavedDir(), TEXT("WebConnection.txt"));
	FArchive* pArWriter = IFileManager::Get().CreateFileWriter(*fstrFullPath);

	if (pArWriter == nullptr)
		return;


	//*pArWriter << pTmpWebConnection->m_fstrHost;
	//*pArWriter << pTmpWebConnection->m_fstrUrl;
	*pArWriter << *pTmpWebConnection;
	pArWriter->Close();
	//pTmpWebConnection.reset();
	delete pTmpWebConnection;
	pTmpWebConnection = nullptr;


	// WebConnection.txt ���� �� ��������
	TSharedPtr<FArchive> pFileReader = MakeShareable(IFileManager::Get().CreateFileReader(*fstrFullPath));

	if (!(pFileReader.IsValid()))
		return;

	//FString fstrHost;
	//FString fstrURI;
	pTmpWebConnection = NewObject<UWebConnection>(this);
	//*pFileReader.Get() << fstrHost;
	//*pFileReader.Get() << fstrURI;
	*pFileReader.Get() << *pTmpWebConnection;
	// ����?? << �����ڳ�?? >> �̰� �� ����
	pFileReader->Close();
	//AB_LOG(Warning, TEXT("WebConnection : Host %s , URI %s"), *fstrHost, *fstrURI);
	AB_LOG(Warning, TEXT("WebConnection : Host %s , URI %s"), *pTmpWebConnection->m_fstrHost, *pTmpWebConnection->m_fstrUrl);
	// �Ϳ� �ΰ� ������ �����ϸ� �����Ͱ� ������ ����!!!! �� �� ���� �����Դϴ�. ����Ʈ�� �����ðڽ��ϱ�? ..�� �����ٴ� ����̾�

	delete pTmpWebConnection;
	pTmpWebConnection = nullptr;
}

void UABGameInstance::HowToUseTheSerialization()
{
	// file extension : ���� Ȯ����
	FString		fstrPackageName		= TEXT("/Temp/SavedWebConnection");
	UPackage*	pPackage			= CreatePackage(nullptr, *fstrPackageName);
	FString		fstrPackageFileName
		= FPackageName::LongPackageNameToFilename(fstrPackageName, FPackageName::GetAssetPackageExtension());

	UWebConnection* pTmpWebConnection = NewObject<UWebConnection>(pPackage);
	pTmpWebConnection->m_fstrHost = TEXT("127.0.0.7");
	pTmpWebConnection->m_fstrUrl = TEXT("/");

	if (UPackage::SavePackage(pPackage, pTmpWebConnection, RF_Standalone, *fstrPackageFileName))
	{
		UPackage* pSavedPackage = ::LoadPackage(nullptr, *fstrPackageFileName, LOAD_None);
		TArray<UObject *> arrObjectsInPackage;
		GetObjectsWithOuter(pSavedPackage, arrObjectsInPackage, false);

		for (const auto& EachObject : arrObjectsInPackage)
		{
			UWebConnection* WebConnectionFromFile = Cast<UWebConnection>(EachObject);
			if (WebConnectionFromFile)
			{
				AB_LOG(Warning, TEXT("WebConnection From File : Host %s , URI %s")
					, *WebConnectionFromFile->m_fstrHost, *WebConnectionFromFile->m_fstrUrl);
			}
		}
	}
}