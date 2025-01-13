#include "pch.h"
#include "CommandTypes.h"
#include "InputManagerSystem.h"
#include "GameSystem.h"
#include "ShopSystem.h"
#include "functional"


shared_ptr<ShopSystem> GShopSystem = make_shared<ShopSystem>();

void ShopSystem::EnterSystem()
{
	GetRandomItems();

	MainMenu();
}

void ShopSystem::MainMenu()
{
	int input = InputManagerSystem::GetInput<int>(
		"상점 메뉴",
		{ "1. 아이템 구입" , "2. 아이템 매각", "3. 돌아가기"},
		RangeValidator<int>(1, 3)
	);

	if (input == 1)
	{
		BuyMenu();
	}
	else if (input == 2)
	{
		SellMenu();
	}
	else if (input == 3)
	{
		GSystemContext->RunSystem(GBattleSystem);
		GSystemContext->MoveSystem(GBattleSystem, GShopSystem);
	}
}

void ShopSystem::BuyMenu()
{
	//string title = "아이템 구입";

	//int itemSize= itemList.size();
	//vector<string> options(itemSize, "");
	//int index = 1;

	///*for (int i = 0; i < itemSize; i++)
	//{
	//	options[i] = (to_string(index++) + ". " + itemList[i]->name);
	//}*/
	//options.push_back(to_string(index) + ". 돌아가기");

	//int input = InputManagerSystem::GetInput<int>(title, options, RangeValidator<int>(1, index));

	//if (input < itemSize)
	//{
	//	auto buyCommand = make_shared<BuyCommand>(player, itemList[input]);
	//	GInvoker->ExecuteCommand(buyCommand);
	//}
}

void ShopSystem::SellMenu()
{
	//player->인벤토리 출력
	//인벤토리 사이즈 받아 조건 확인
}

void ShopSystem::GetRandomItems()
{
	//todo: 랜덤 아이템 구현
	/*itemList.clear();
	itemList.push_back(make_shared<Item>("체력 포션", "체력을 50 회복합니다.", 50));
	itemList.push_back(make_shared<Item>("체력 포션", "체력을 50 회복합니다.", 50));
	itemList.push_back(make_shared<Item>("공격력 포션", "공격력을 15 상승시킵니다.", 100));
	itemList.push_back(make_shared<Item>("공격력 포션", "공격력을 15 상승시킵니다.", 100));*/
}