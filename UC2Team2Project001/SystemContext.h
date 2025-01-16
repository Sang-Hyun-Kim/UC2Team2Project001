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
	string characterName;
	int damage;
	int hp;

	IEnterSystemEvent(const std::string& _name, int _dmg, int _inHP) : characterName(_name), damage(_dmg), hp(_inHP)
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

	void OnEvent(const std::shared_ptr<IEvent> _event) override;
	inline shared_ptr<class Player> GetPlayer() 
	{
		return player; 
	}

	shared_ptr<GameSystem> GetCurrentSystem()
	{ 
		return currentSystem; 
	}
private:
	void MoveSystem(SystemType _to, SystemType _from);

public:
	void CreateCharacter(string _name);

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

