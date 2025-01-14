#pragma once
#include "pch.h"
#include "GameSystem.h"
#include "ShopSystem.h"
#include "GlobalEventManager.h"
#include "IEventTypes.h"
#include "Item.h"
#include "PlayerCharacter.h"
#include "Inventory.h"
#include "SystemContext.h"


class ICommand
{
public:
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual ~ICommand() = default;
};

class SellCommand : public ICommand
{
public:
	SellCommand(shared_ptr<Player> player, shared_ptr<Item> item) :player(player), item(item) {}

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
	shared_ptr<Player> player;
	shared_ptr<Item> item;
};

class BuyCommand : public ICommand
{
public:
	BuyCommand(shared_ptr<Player> player, vector<shared_ptr<Item>>& itemList, int index) :player(player), itemList(itemList), index(index) {}

	void Execute() override // Creature 로 둔다면 형변환
	{
		int gold = player->InventoryComponent->getGold();
		auto item = itemList[index];
		int itemValue = item->getValue();

		if (gold >= itemValue)
		{
			auto Event = make_shared<IItemPurchasedEvent>(player->GetName(), item->getName(), item->getValue());
			GlobalEventManager::Get().Notify(Event);

			player->InventoryComponent->removeGold(itemValue);
			player->InventoryComponent->addItem(item);
			itemList.erase(itemList.begin() + index);
		}
		else
		{
			cout << "골드가 부족합니다.\n";
		}
	}

	void Undo() override
	{

		/*auto Event = make_shared<IItemSoldEvent>(p->GetName(), item->name, item->cost);
		GlobalEventManager::Get().Notify(Event);*/
	}

private:
	shared_ptr<Player> player;
	vector<shared_ptr<Item>>& itemList;
	int index;
};