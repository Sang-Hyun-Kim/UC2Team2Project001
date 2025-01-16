#pragma once
#include "pch.h"
#include "EventManagerSystem.h"
#include "IEventTypes.h"

class LobbySystem;
class BattleSystem;
class ShopSystem;
class Player;
class GameSystem;

enum class SystemType
{
	LOBBY,
	BATTLE,
	SHOP
};

class IEnterSystemEvent : public IEvent
{
public:
	string CharacterName;
	int Damage;
	int HP;

	IEnterSystemEvent(const std::string& name, int dmg, int InHP) : CharacterName(name), Damage(dmg), HP(InHP)
	{
	}
};

class SystemContext : public IEventManagerSystem
{
public:
	SystemContext();
	~SystemContext();

	SystemContext(const SystemContext&) = delete;
	SystemContext& operator=(const SystemContext&) = delete;

	void Update();

	void OnEvent(const std::shared_ptr<IEvent> ev) override;
	inline shared_ptr<class Player> GetPlayer() { return player; }

	shared_ptr<GameSystem> GetCurrentSystem() { return currentSystem; }
private:
	void MoveSystem(SystemType to, SystemType from);

public:
	void CreateCharacter(string name);

	shared_ptr<GameSystem> currentSystem = nullptr;

	shared_ptr<LobbySystem> lobbySystem;
	shared_ptr<BattleSystem> battleSystem;
	shared_ptr<ShopSystem> shopSystem;

	shared_ptr<Player> player;
};

extern shared_ptr<SystemContext> GSystemContext;

class IMoveSystemEvent : public IEvent
{
public:
	SystemType to;
	SystemType from;

	IMoveSystemEvent(SystemType _to, /*shared_ptr<GameSystem> _curSystem*/ SystemType _from) : to(_to), from(_from)
	{
		//from = _curSystem->GetSystemType();
	}
};

