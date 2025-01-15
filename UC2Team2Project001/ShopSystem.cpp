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
	auto player = GSystemContext->GetPlayer();

	player->InventoryComponent->displayInventory();

	InputManagerSystem::PauseUntilEnter();

	state = make_shared<ShopMainState>();
}

void ShopSystem::BuyMenu()
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
	string title = "==== 아이템 판매 ====";

	auto player = GSystemContext->GetPlayer();
	
	int lastIndex = player->InventoryComponent->getInventorySize() + 1;
	vector<string> inventoryInfos = player->InventoryComponent->GetInventoryInfoWithString(1);
	
	inventoryInfos.push_back(to_string(lastIndex) + ". 돌아가기");

	int input = InputManagerSystem::GetInput<int>(title, inventoryInfos, RangeValidator<int>(1, lastIndex));

	if (input == lastIndex)
	{
		state = make_shared<ShopMainState>();
	}
	else
	{
		//팔기
		//몇 개?
		auto item = player->InventoryComponent->GetItemWithIndex(input - 1);
		auto itemCount = player->InventoryComponent->getItemCount(input - 1);
		auto itemValue = item->getValue();

		int sellCount = InputManagerSystem::GetInput<int>("판매할 갯수를 입력해주세요. ", {}, RangeValidator<int>(1, itemCount));
		player->InventoryComponent->removeItem(input, sellCount);
		int totalGainGold = itemValue * sellCount;
		player->InventoryComponent->addGold(totalGainGold);
		cout << item->getName() + "(을)를 " + to_string(itemValue) + "개 팔아 " + to_string(totalGainGold) + "골드를 얻었습니다." << endl;
	}
}

void ShopSystem::GetRandomItems()
{
	itemList.clear();

	for (int i = 0; i < 5; i++)
	{
		itemList.push_back(ItemManager::GetInstance().getRandomItem());
	}
}

void ShopSystem::OnEvent(const std::shared_ptr<IEvent> ev)
{
	// 캐릭터가 (상품 가격 감소) 패시브 스킬을 획득하면 가격이 내려가도록 조정
}
