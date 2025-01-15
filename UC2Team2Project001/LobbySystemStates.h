#pragma once
#include "pch.h"
#include "LobbySystem.h"


class LobbyMainState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* system) override
	{
		auto lobby = dynamic_cast<LobbySystem*>(system);

		if (lobby)
		{
			lobby->MainMenu();
		}
	}
};

class LobbyCreateState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* system) override
	{
		auto lobby = dynamic_cast<LobbySystem*>(system);

		if (lobby)
		{
			lobby->CreatePlayerMenu();
		}
	}
};