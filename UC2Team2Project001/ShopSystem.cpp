#include "pch.h"
#include "CommandTypes.h"
#include "InputManagerSystem.h"
#include "GameSystem.h"
#include "ShopSystem.h"
#include "functional"
#include "ItemManager.h"


shared_ptr<ShopSystem> GShopSystem = make_shared<ShopSystem>();

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
		ExitSystem(GBattleSystem);
		break;
	default:
		break;
	}
}

void ShopSystem::MainMenu()
{
	int input = InputManagerSystem::GetInput<int>(
		"\n ==== 상점 메뉴 ====",
		{ "1. 인벤토리 보기" , "2. 아이템 사기", "3. 돌아가기" },
		"",
		RangeValidator<int>(1, 3)
	);

	state = input;
}

void ShopSystem::DisplayInventory()
{
	cout << "\n";
	player->InventoryComponent->displayInventory();

	if (cin.rdbuf()->in_avail() > 0) // 버퍼에 읽을 수 있는 데이터가 있으면
	{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 버퍼에 있는 모든 입력을 무시
	};

	cout << "엔터를 눌러 계속하세요...\n";

	cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 엔터를 누를 때까지 대기

	state = MAIN;
}

void ShopSystem::BuyMenu()
{
	string title = "\n==== 아이템 구입 ====";

	int itemSize = (int)itemList.size();
	vector<string> options(itemSize, "");
	int index = 1;

	for (int i = 0; i < itemSize; i++)
	{
		options[i] = (to_string(index++) + ". " + itemList[i]->getName() + " 가격: " + to_string(itemList[i]->getValue()));
	}
	options.push_back(to_string(index) + ". 돌아가기");

	int input = InputManagerSystem::GetInput<int>(title, options, "", RangeValidator<int>(1, index));

	cout << "\n";

	if (input <= itemSize)
	{
		auto buyCommand = make_shared<BuyCommand>(player, itemList, input - 1);
		GInvoker->ExecuteCommand(buyCommand);
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