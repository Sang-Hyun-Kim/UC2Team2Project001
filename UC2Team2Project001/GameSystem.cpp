#include "pch.h"
#include "GameSystem.h"

void GameSystem::ExitSystem(SystemType nextType)
{
	auto moveEvent = make_shared<IMoveSystemEvent>(nextType, GetSystemType());
	GlobalEventManager::Get().Notify(moveEvent);
}
