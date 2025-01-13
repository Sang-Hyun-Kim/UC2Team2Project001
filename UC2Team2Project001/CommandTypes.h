#pragma once
#include "pch.h"
#include "GameSystem.h"
#include "ShopSystem.h"
#include "GlobalEventManager.h"
#include "IEventTypes.h"

class ICommand
{
public:
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual ~ICommand() = default;
};

class MoveCommand : public ICommand
{
public:
	MoveCommand(shared_ptr<GameSystem>to, shared_ptr<GameSystem>from) : to(to), from(from) {}

	void Execute() override
	{
		GSystemContext->RunSystem(to);
		GSystemContext->MoveSystem(to, from);
		auto Event = make_shared<IMoveEvent>("현 위치", "목적지");
		GlobalEventManager::Get().Notify(Event);
	}

	void Undo() override
	{
		GSystemContext->RunSystem(from);
		GSystemContext->MoveSystem(from, to);
		auto Event = make_shared<IMoveEvent>("현 위치", "목적지");
		GlobalEventManager::Get().Notify(Event);
	}

private:
	shared_ptr<GameSystem> to;
	shared_ptr<GameSystem> from;
};

class SellCommand : public ICommand
{
public:
	SellCommand(shared_ptr<Character> player, shared_ptr<Item> item) :player(player), item(item) {}

	void Execute() override
	{
		/*auto Event = make_shared<IItemSoldEvent>(player->GetName(), item->name, item->cost);
		GlobalEventManager::Get().Notify(Event);*/
	}

	void Undo() override
	{
		/*auto Event = make_shared<IItemPurchasedEvent>(player->GetName(), item->name, item->cost);
		GlobalEventManager::Get().Notify(Event);*/
	}

private:
	shared_ptr<Character> player;
	shared_ptr<Item> item;
};

class BuyCommand : public ICommand
{
public:
	BuyCommand(shared_ptr<Character> player, shared_ptr<Item> item) :player(player), item(item) {}

	void Execute() override // Creature 로 둔다면 형변환
	{
		auto p = dynamic_pointer_cast<Character>(player);
		if (p != nullptr)
		{
			/*auto Event = make_shared<IItemPurchasedEvent>(p->GetName(), item->name, item->cost);
			GlobalEventManager::Get().Notify(Event);*/
		}
	}

	void Undo() override
	{
		auto p = dynamic_pointer_cast<Character>(player);

		if (p != nullptr)
		{
			/*auto Event = make_shared<IItemSoldEvent>(p->GetName(), item->name, item->cost);
			GlobalEventManager::Get().Notify(Event);*/
		}
	}

private:
	shared_ptr<Character> player;
	shared_ptr<Item> item;
};