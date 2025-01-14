#include "pch.h"
#include "SystemContext.h"
#include "LobbySystem.h"
#include "BattleSystem.h"
#include "ShopSystem.h"
#include "PlayerCharacter.h"

shared_ptr<SystemContext> GSystemContext = make_shared<SystemContext>();

SystemContext::SystemContext()
{
	lobbySystem = new LobbySystem();
	battleSystem = new BattleSystem();
	shopSystem = new ShopSystem();

	currentSystem = lobbySystem;
}

SystemContext::~SystemContext()
{
	delete battleSystem;
	delete shopSystem;
	delete lobbySystem;
}

void SystemContext::Update()
{
	currentSystem->Update();
}

void SystemContext::MoveSystem(SystemType to, SystemType from)
{
	// System from 에서 System to 로 이동

	if (to != from)
	{
		switch (to)
		{
		case SystemType::LOBBY:
			currentSystem = lobbySystem;
			break;
		case SystemType::BATTLE:
			currentSystem = battleSystem;
			break;
		case SystemType::SHOP:
			currentSystem = shopSystem;
			break;
		default:
			break;
		}

		currentSystem->EnterSystem();
	}
}

void SystemContext::CreateCharacter(string name)
{
	player = make_shared<Player>("Player");
}

void SystemContext::OnEvent(const std::shared_ptr<IEvent>& ev)
{
	if (auto move = std::dynamic_pointer_cast<IMoveSystemEvent>(ev))
	{
		MoveSystem(move->to, move->from);
	}
	else if (auto create = std::dynamic_pointer_cast<ICharacterCreateEvent>(ev))
	{
		CreateCharacter(create->name);
	}
	else if (auto gameOver = std::dynamic_pointer_cast<IPlayerDefeatEvent>(ev))
	{
		player.reset();
	}
}

shared_ptr<Player> SystemContext::GetPlayer(SystemType systemType)
{
	if (currentSystem->GetSystemType() == systemType)
	{
		return player;
	}
	else
	{
		throw std::runtime_error("현재 실행 중인 시스템 외에서 플레이어에게 접근을 시도했습니다.");
	}
}
