#include "pch.h"
#include "ShopSystem.h"
#include "BattleSystem.h"
#include "InputManagerSystem.h"
#include "ItemManager.h"
#include "Invoker.h"
#include "CommandTypes.h"
#include "ShopSystemStates.h"

void ShopSystem::EnterSystem()
{
	GetRandomItems();
	state = make_shared<ShopMainState>();
}

//void ShopSystem::Update()
//{
//	switch (state)
//	{
//	case MAIN:
//		MainMenu();
//		break;
//	case INVENTORY:
//		DisplayInventory();
//		break;
//	case BUY:
//		BuyMenu();
//		break;
//	case SELL:
//		SellMenu();
//		break;
//	case EXIT:
//		ExitSystem(SystemType::BATTLE);
//		break;
//	default:
//		break;
//	}
//}

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
		state = make_shared<ShopDisplayInventoryState>();
	}
	else if (input == 2)
	{
		state = make_shared<ShopBuyState>();
	}
	else if (input == 3)
	{
		state = make_shared<ShopSellState>();
	}
	else if (input == 4)
	{
		ExitSystem(SystemType::BATTLE);
	}
}

void ShopSystem::DisplayInventory()
{
	CLEAR;
	auto player = GSystemContext->GetPlayer(GetSystemType());

	player->InventoryComponent->displayInventory();

	InputManagerSystem::PauseUntilEnter();

	state = make_shared<ShopMainState>();
}

void ShopSystem::BuyMenu()
{
	CLEAR;

	string title = "==== 아이템 구매 ====";

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
	else state = make_shared<ShopMainState>();
}

void ShopSystem::SellMenu()
{
	//player->인벤토리 출력
	//인벤토리 사이즈 받아 조건 확인
	auto player = GSystemContext->GetPlayer(GetSystemType());

	int inventorySize = player->InventoryComponent->getInventorySize();
	player->InventoryComponent->displayInventory(0);

	string title = "==== 아이템 판매 ====";

	int input = InputManagerSystem::GetInput<int>(title, {}, RangeValidator<int>(1, inventorySize));
}

void ShopSystem::GetRandomItems()
{
	itemList.clear();

	for (int i = 0; i < 5; i++)
	{
		itemList.push_back(ItemManager::GetInstance().getRandomItem());
	}
}

void ShopSystem::OnEvent(const std::shared_ptr<IEvent>& ev)
{
	// 캐릭터가 (상품 가격 감소) 패시브 스킬을 획득하면 가격이 내려가도록 조정
}
