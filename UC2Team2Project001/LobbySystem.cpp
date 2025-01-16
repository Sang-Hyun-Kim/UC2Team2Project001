#include "pch.h"
#include "LobbySystem.h"
#include "LobbySystemStates.h"
#include "PlayerCharacter.h"
#include "ICharacterEventTypes.h"

LobbySystem::LobbySystem()
{
}

void LobbySystem::EnterSystem()
{
	// 처음 로비에 들어왔을 때
	// 게임 시작, 또는 게임 패배 후 돌아왔을 때
	// 지금 굳이 필요 없는 기능, 추후 확장=> 로비가 시작되었을 때 해야하는 것들
	// 로그인, 로그인 검증 등
	// 죽었으면 MAIN
	// 
	state = make_shared<LobbyMainState>();
}

//void LobbySystem::Update()
//{
//	CLEAR;
//
//	switch (state)
//	{
//	case LobbyState::MAIN:
//		MainMenu();
//		break;
//	case LobbyState::START:
//		StartMenu();
//		break;
//	case LobbyState::EXIT:
//		exit(1);
//		break;
//	default:
//		break;
//	}
//}

void LobbySystem::MainMenu()
{
	int input = InputManagerSystem::GetInput<int>
	(
		"==== 게임 로비 ====",
		{ "1. 게임 시작" , "2. 게임 종료" },
		RangeValidator<int>(1, 2)
	);
	
	if (input == 1)
	{
		state = make_shared<LobbyCreateState>();
	}
	else
	{
		exit(1);
	}
}

void LobbySystem::CreatePlayerMenu()
{
	//CLEAR;
	string userName = InputManagerSystem::GetInput(
		"캐릭터의 이름을 입력해주세요.(중간 공백 허용, 최대12자)",
		{},
		NameRangeValidator(1, 12),
		NameSpaceValidator(),
		NoSpecialCharValidator()
	);

	auto createEvent = make_shared<ICharacterCreateEvent>(userName);
	GlobalEventManager::Get().Notify(createEvent);
	//GSystemContext->CreateCharacter(userName);
	auto player = GSystemContext->GetPlayer();
	CharacterUtility::PrintStatus(player.get());

	InputManagerSystem::PauseUntilEnter();

	ExitSystem(SystemType::BATTLE);
}

void LobbySystem::OnEvent(const std::shared_ptr<IEvent> ev)
{
}
