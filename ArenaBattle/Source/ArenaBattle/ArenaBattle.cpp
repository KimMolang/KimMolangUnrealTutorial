// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"


DEFINE_LOG_CATEGORY(ArenaBattle);

// 지금까지 우리가 제작한 ArenaBattle이라는 게임 프로젝트는
// ArenaBattle이라는 동일한 이름의 C++ 모듈이 추가된 형태입니다.
// 이렇게 언리얼 엔진의 C++ 개발 환경은 하나의 게임 프로젝트에
// 하나의 모듈을 사용하는 것이 일반적입니다.
// 언리얼 엔진에서는 ArenaBattle 모듈과 같이 게임 제작에 사용되는 로직을 담은
// 기본 모듈을 주 게임 모듈(Primary Game Module)이라고 합니다.
IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, ArenaBattle, "ArenaBattle" );

// 하지만 모듈을 직접 만들 수 있다규
// WebService 모듈을 만들어 보자.