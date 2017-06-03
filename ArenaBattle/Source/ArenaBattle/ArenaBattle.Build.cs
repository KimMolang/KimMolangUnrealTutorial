// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ArenaBattle : ModuleRules
{
	public ArenaBattle(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core"
                                                            , "CoreUObject"
                                                            , "Engine"
                                                            , "InputCore"
                                                            , "WebService"});
        // 다른 모듈이라 빌드할 때 WebService 얘 모듈도 같이 해주세요!! 라고 해줘야함
        // 그러면 UBT이 WebService의 include와 Library 경로를 자동으로
        // 빌드 설정에 추가해줌!

        PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
