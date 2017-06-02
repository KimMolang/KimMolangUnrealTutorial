// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class WebService : ModuleRules
{
	public WebService(TargetInfo Target)
	{
        // 현재 모듈이 참조할 외부 모듈의 목록을 지정합니다.
        // 각각 public과 private 폴더에서 참고할 모듈을 지정하는데 사용됩니다.
        // Spectify a lisf of external modules to refer to the current module.
        // Used to specify modules to be referenced in Public and Privete folders respectively.
        // Public 프로퍼티에는 헤더파일이 참고할 모듈(외부 모듈에 공개할 파일), 
        // Private 프로퍼티에는 소스코드에서만 참고할 모듈(내부 모듈에서 사용할 파일)을 지정하면 됩니다.
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"/*, "InputCore"*/});
        // Core, CoreUObject, Engine : 언리얼 엔진과 연동되는 기능
        // InputCore : 입력에 관한 모듈

        PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
