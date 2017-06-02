// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class WebService : ModuleRules
{
	public WebService(TargetInfo Target)
	{
        // ���� ����� ������ �ܺ� ����� ����� �����մϴ�.
        // ���� public�� private �������� ������ ����� �����ϴµ� ���˴ϴ�.
        // Spectify a lisf of external modules to refer to the current module.
        // Used to specify modules to be referenced in Public and Privete folders respectively.
        // Public ������Ƽ���� ��������� ������ ���(�ܺ� ��⿡ ������ ����), 
        // Private ������Ƽ���� �ҽ��ڵ忡���� ������ ���(���� ��⿡�� ����� ����)�� �����ϸ� �˴ϴ�.
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"/*, "InputCore"*/});
        // Core, CoreUObject, Engine : �𸮾� ������ �����Ǵ� ���
        // InputCore : �Է¿� ���� ���

        PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
