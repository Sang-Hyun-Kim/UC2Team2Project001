#pragma once
#include "pch.h"
#include "GameSystem.h"
#include "ShopSystem.h"
#include "ISystemTypes.h"
#include "GlobalEventManager.h"

#include "Item.h"
#include "PlayerCharacter.h"
#include "Inventory.h"
#include "SystemContext.h"

#include "IItemEventTypes.h"
#include "ICombatEventTypes.h"
#include "ICharacterEventTypes.h"

#include "SkillManager.h"
#include "USkillComponent.h"

#include "CombatComponent.h"

#include "LobbySystemStates.h"
#include "BattleSystemStates.h"
#include "ShopSystemStates.h"

class ICommand
{
public:
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual ~ICommand() = default;
};

class SellItemCommand : public ICommand
{
public:
	SellItemCommand(vector<shared_ptr<Item>>& _itemList, int _index) : itemList(itemList), index(_index) 
	{
	}

	void Execute() override
	{
		auto player = GSystemContext->GetPlayer();

		auto item = player->inventoryComponent->GetItemWithIndex(index - 1);
		auto itemCount = player->inventoryComponent->getItemCount(index - 1);
		auto itemValue = item->getValue();

		int sellCount = InputManagerSystem::GetInput<int>("판매할 갯수를 입력해주세요. ", {}, RangeValidator<int>(1, itemCount));

		player->inventoryComponent->removeItem(index - 1, sellCount);
		int totalGainGold = itemValue * sellCount;
		player->inventoryComponent->addGold(totalGainGold);
		cout << item->getName() + "(을)를 " + to_string(itemValue) + "개 팔아 " + to_string(totalGainGold) + "골드를 얻었습니다." << endl;
	}

	void Undo() override
	{

	}

private:
	vector<shared_ptr<Item>> itemList;
	int index;
};

class BuyItemCommand : public ICommand
{
public:
	BuyItemCommand(shared_ptr<Player> _player, vector<shared_ptr<Item>>& _itemList, int _index) :player(_player), itemList(_itemList), index(_index) {}

	void Execute() override // Creature 로 둔다면 형변환
	{
		int gold = player->inventoryComponent->getGold();
		auto item = itemList[index];
		int itemValue = item->getValue();

		if (gold >= itemValue)
		{
			auto Event = make_shared<IItemPurchasedEvent>(player->GetName(), item->getName(), item->getValue());
			GlobalEventManager::Get().Notify(Event);

			player->inventoryComponent->removeGold(itemValue);
			player->inventoryComponent->addItem(item);
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

class SystemMoveCommand : public ICommand
{
public:
	SystemMoveCommand(SystemType _to, SystemType _from, string _toName, string _fromName) : to(_to), from(_from), toName(_toName), fromName(_fromName)
	{
	}

	void Execute() override
	{
		auto event = make_shared<IMoveSystemEvent>(to, from, toName, fromName);
		GlobalEventManager::Get().Notify(event);
	}

	void Undo() override
	{
	}

private:
	SystemType to;
	SystemType from;
	string toName;
	string fromName;
};

class SystemChangeStateCommand : public ICommand
{
public:
	SystemChangeStateCommand(shared_ptr<ISystemState> _state): state(_state)
	{
	}

	void Execute() override
	{
		GSystemContext->GetCurrentSystem()->SetState(state);
	}

	void Undo() override
	{
	}

private:
	shared_ptr<ISystemState> state;
};

class ExitCommand : public ICommand
{
public:
	ExitCommand() 
	{
	}

	void Execute() override
	{
		exit(1);
		/*auto Event = make_shared<IItemSoldEvent>(player->GetName(), item->name, item->cost);
		GlobalEventManager::Get().Notify(Event);*/
	}

	void Undo() override
	{
		/*auto Event = make_shared<IItemPurchasedEvent>(player->GetName(), item->name, item->cost);
		GlobalEventManager::Get().Notify(Event);*/
	}

private:
};

class CreateCharacterCommand : public ICommand
{
public:
	CreateCharacterCommand(shared_ptr<Player> _player, shared_ptr<Item> _item) :player(_player), item(_item) {}

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

class UseSkillCommand : public ICommand
{
public:
	UseSkillCommand(string _skillName): skillName(_skillName)
	{
	}

	void Execute() override
	{
		auto playerAttackEv = make_shared<IPlayerBattleAttackEvent>();
		GlobalEventManager::Get().Notify(playerAttackEv);

		auto player = GSystemContext->GetPlayer();

		if (player->skillManager->UseSkill(SkillType::ACTIVE, skillName))
		{

		}
		else
		{

		}
	}

	void Undo() override
	{
	}

private:
	string skillName;
};

class UseItemCommand : public ICommand
{
public:
	UseItemCommand(int _index) : index(_index)
	{
	}

	void Execute() override
	{
		auto player = GSystemContext->GetPlayer();
		player->inventoryComponent->useItem(index);
	}

	void Undo() override
	{
	}

private:
	int index;
};

class AddSkillCommand : public ICommand
{
public:
	AddSkillCommand(type_index _skillType) 
		:skillType(_skillType) 
	{
	}

	void Execute() override
	{
		auto player = GSystemContext->GetPlayer();
		SkillManager::GetInstance().AddSelectSkillToCharacter(skillType, player.get());
	}

	void Undo() override
	{
	}

private:
	type_index skillType;
};

