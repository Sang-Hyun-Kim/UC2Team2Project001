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

void ShopSystem::EnterSystem()
{
	GetRandomItemsAndSkills();
	state = make_shared<ShopMainState>();
}

void ShopSystem::MainMenu()
{
	CLEAR;

	int input = InputManagerSystem::GetInput<int>(
		"==== 상점 메뉴 ====",
		{ "1. 인벤토리 보기" , "2. 아이템 구매", "3. 아이템 판매", "4. 돌아가기" },
		RangeValidator<int>(1, 4)
	);

	if (input == 1)
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<ShopDisplayInventoryState>());
		GInvoker->ExecuteCommand(cmd);
	}
	else if (input == 2)
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<ShopBuyItemState>());
		GInvoker->ExecuteCommand(cmd);
	}
	else if (input == 3)
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<ShopSellState>());
		GInvoker->ExecuteCommand(cmd);
	}
	else if (input == 4)
	{
		auto cmd = make_shared<SystemMoveCommand>(SystemType::BATTLE, GetSystemType(), "배틀", "상점");
		GInvoker->ExecuteCommand(cmd);
	}
}

void ShopSystem::DisplayInventory()
{
	CLEAR;
	auto player = GSystemContext->GetPlayer();

	player->InventoryComponent->displayInventory();

	InputManagerSystem::PauseUntilEnter();

	state = make_shared<ShopMainState>();
}

void ShopSystem::BuyItemMenu()
{
	CLEAR;

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
		auto player = GSystemContext->GetPlayer();
		auto buyCommand = make_shared<BuyItemCommand>(player, itemList, input - 1);
		GInvoker->ExecuteCommand(buyCommand);

		InputManagerSystem::PauseUntilEnter();
	}
	else state = make_shared<ShopMainState>();
}

void ShopSystem::SellMenu()
{
	//player->인벤토리 출력
	//인벤토리 사이즈 받아 조건 확인
	CLEAR;
	string title = "==== 아이템 판매 ====";

	auto player = GSystemContext->GetPlayer();
	
	int lastIndex = player->InventoryComponent->getInventorySize() + 1;
	vector<string> inventoryInfos = player->InventoryComponent->GetInventoryInfoWithString(1);
	
	inventoryInfos.push_back(to_string(lastIndex) + ". 돌아가기");

	int input = InputManagerSystem::GetInput<int>(title, inventoryInfos, RangeValidator<int>(1, lastIndex));

	if (input == lastIndex)
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<ShopMainState>());
		GInvoker->ExecuteCommand(cmd);
	}
	else
	{
		auto cmd = make_shared<SellItemCommand>(itemList, input);
		GInvoker->ExecuteCommand(cmd);
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

void ShopSystem::OnEvent(const std::shared_ptr<IEvent> ev)
{
	// 캐릭터가 (상품 가격 감소) 패시브 스킬을 획득하면 가격이 내려가도록 조정
}
