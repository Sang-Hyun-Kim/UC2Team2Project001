#include "pch.h"
#include "GameSystem.h"

void GameSystem::Update()
{
	//ChangeState();
	if (state)
	{
		state->Excute(this);
	}
	else
	{
		throw std::runtime_error("GameSystem의 state가 nullptr입니다.");
	}
}

void GameSystem::ExitSystem(SystemType _nextType)
{
	auto moveEvent = make_shared<IMoveSystemEvent>(_nextType, GetSystemType());
	GlobalEventManager::Get().Notify(moveEvent);
}
