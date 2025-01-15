#include "pch.h"
#include "ShopSystem.h"
#include "BattleSystem.h"
#include "InputManagerSystem.h"
#include "ItemManager.h"
#include "Invoker.h"
#include "CommandTypes.h"

void ShopSystem::EnterSystem()
{
	GetRandomItems();
	state = ShopState::MAIN;
}

void ShopSystem::Update()
{
	switch (state)
	{
	case MAIN:
		MainMenu();
		break;
	case INVENTORY:
		DisplayInventory();
		break;
	case BUY:
		BuyMenu();
		break;
	case EXIT:
		ExitSystem(SystemType::BATTLE);
		break;
	default:
		break;
	}
}

void ShopSystem::MainMenu()
{
	CLEAR;

	int input = InputManagerSystem::GetInput<int>(
		"==== 상점 메뉴 ====",
		{ "1. 인벤토리 보기" , "2. 아이템 사기", "3. 돌아가기" },
		RangeValidator<int>(1, 3)
	);

	state = input;
}

void ShopSystem::DisplayInventory()
{
	CLEAR;
	auto player = GSystemContext->GetPlayer(GetSystemType());

	player->InventoryComponent->displayInventory();

	InputManagerSystem::PauseUntilEnter();

	state = MAIN;
}

void ShopSystem::BuyMenu()
{
	CLEAR;

	string title = "==== 아이템 구입 ====";

	int itemSize = itemList.size();
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
		auto player = GSystemContext->GetPlayer(GetSystemType());
		auto buyCommand = make_shared<BuyCommand>(player, itemList, input - 1);
		GInvoker->ExecuteCommand(buyCommand);

		InputManagerSystem::PauseUntilEnter();
	}
	else state = MAIN;
}

void ShopSystem::SellMenu()
{
	//player->인벤토리 출력
	//인벤토리 사이즈 받아 조건 확인
}

void ShopSystem::GetRandomItems()
{
	itemList.clear();

	for (int i = 0; i < 5; i++)
	{
		itemList.push_back(ItemManager::GetInstance().getRandomItem());
	}
}