#include "pch.h"
#include "InputManagerSystem.h"

#include "ShopSystem.h"
#include "ShopSystemStates.h"

#include "ItemManager.h"
#include "CommandTypes.h"
#include "Invoker.h"

#include "Skill.h"
#include "SkillManager.h"
#include "USkillComponent.h"
#include "ConsoleLayout.h"

void ShopSystem::EnterSystem()
{
	ConsoleLayout::GetInstance().AllClear();
	GetRandomItemsAndSkills();
	state = make_shared<ShopMainState>();
}

void ShopSystem::MainMenu()
{
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftTop);
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::RightTop);
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);

	auto player = GSystemContext->GetPlayer();

	player->inventoryComponent->displayInventory();

	int input = InputManagerSystem::GetInput<int>(
		"==== 상점 메뉴 ====",
		{ "1. 아이템 구매", "2. 아이템 판매", "3. 돌아가기" },
		RangeValidator<int>(1, 3)
	);


	if (input == 1)
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<ShopBuyItemState>());
		GInvoker->ExecuteCommand(cmd);
	}
	else if (input == 2)
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<ShopSellState>());
		GInvoker->ExecuteCommand(cmd);
	}
	else if (input == 3)
	{
		auto cmd = make_shared<SystemMoveCommand>(SystemType::BATTLE, GetSystemType(), "배틀", "상점");
		GInvoker->ExecuteCommand(cmd);
	}
}

void ShopSystem::DisplayInventory()
{
	//CLEAR;
	auto player = GSystemContext->GetPlayer();

	player->inventoryComponent->displayInventory();

	InputManagerSystem::PauseUntilEnter();
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);

	state = make_shared<ShopMainState>();
}

void ShopSystem::BuyItemMenu()
{
	//CLEAR;

	string title = "==== 아이템 구매 ====";

	int itemSize = (int)itemList.size();
	vector<string> options(itemSize, "");
	int index = 1;

	for (int i = 0; i < itemSize; i++)
	{
		options[i] = (to_string(index++) + ". " + itemList[i]->getName() + " 가격: " + to_string(itemList[i]->getValue()));
	}
	options.push_back(to_string(index) + ". 돌아가기");

	int input = InputManagerSystem::GetInput<int>(title, options, RangeValidator<int>(1, index));

	if (input <= itemSize)
	{
		//auto player = GSystemContext->GetPlayer();
		//auto buyCommand = make_shared<BuyItemCommand>(player, itemList, input - 1);
		//GInvoker->ExecuteCommand(buyCommand);
		auto player = GSystemContext->GetPlayer();
		int gold = player->inventoryComponent->getGold();
		auto item = itemList[input-1];
		int itemValue = item->getValue();

		if (gold >= itemValue)
		{
			auto Event = make_shared<IItemPurchasedEvent>(player->GetName(), item->getName(), item->getValue());
			GlobalEventManager::Get().Notify(Event);

			player->inventoryComponent->removeGold(itemValue);
			player->inventoryComponent->addItem(item);
			itemList.erase(itemList.begin() + input-1);
		}
		else
		{
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[Shop] " "골드가 부족합니다.");
		}

		InputManagerSystem::PauseUntilEnter();
		ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);

		ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftTop);
		player->inventoryComponent->displayInventory();
	}
	else state = make_shared<ShopMainState>();
}

void ShopSystem::SellMenu()
{
	//player->인벤토리 출력
	//인벤토리 사이즈 받아 조건 확인
	//CLEAR;
	string title = "==== 아이템 판매 ====";

	auto player = GSystemContext->GetPlayer();
	
	int lastIndex = player->inventoryComponent->getInventorySize() + 1;
	vector<string> inventoryInfos = player->inventoryComponent->GetInventoryInfoWithString(1);
	
	inventoryInfos.push_back(to_string(lastIndex) + ". 돌아가기");

	int input = InputManagerSystem::GetInput<int>(title, inventoryInfos, RangeValidator<int>(1, lastIndex));

	if (input == lastIndex)
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<ShopMainState>());
		GInvoker->ExecuteCommand(cmd);
	}
	else
	{
		//auto cmd = make_shared<SellItemCommand>(itemList, input);
		//GInvoker->ExecuteCommand(cmd);

		auto player = GSystemContext->GetPlayer();

		auto item = player->inventoryComponent->GetItemWithIndex(input - 1);
		auto itemCount = player->inventoryComponent->getItemCount(input - 1);
		auto itemValue = item->getValue();

		int sellCount = InputManagerSystem::GetInput<int>("판매할 갯수를 입력해주세요. ", {}, RangeValidator<int>(1, itemCount));


		for (int i = 0; i < itemCount; i++)
		{
			itemList.push_back(item);
		}

		player->inventoryComponent->removeItem(input - 1, sellCount);
		int totalGainGold = itemValue * sellCount;
		player->inventoryComponent->addGold(totalGainGold);
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[Shop] " + item->getName() + "(을)를 " + to_string(sellCount) + "개 팔아 " + to_string(totalGainGold) + "골드를 얻었습니다.");

		ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftTop);
		player->inventoryComponent->displayInventory();
	}
}

void ShopSystem::BuySkillMenu()
{

}

void ShopSystem::GetRandomItemsAndSkills()
{
	itemList.clear();
	auto player = GSystemContext->GetPlayer();
	//player->skillManager->UseSkill();
	for (int i = 0; i < 6; i++)
	{
		itemList.push_back(ItemManager::GetInstance().getRandomItem());
		vector<type_index> skillTypes = SkillManager::GetInstance().GetUniqueRandomSkillTypes(player.get(), SkillType::ACTIVE, 1);
		//vector<Skill> skills = SkillManager::GetInstance().CreateSkillFromType();
		//skillList.push_back();
		
	}
}

void ShopSystem::OnEvent(const std::shared_ptr<IEvent> _event)
{
	// 캐릭터가 (상품 가격 감소) 패시브 스킬을 획득하면 가격이 내려가도록 조정
}
