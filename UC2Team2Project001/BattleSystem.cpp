#include "pch.h"
#include "BattleSystem.h"
#include "LobbySystem.h"
#include "ShopSystem.h"
#include "StatComponent.h"
#include "Inventory.h"
#include "PlayerCharacter.h"
#include "Monster.h"

BattleSystem::BattleSystem()
{
}

void BattleSystem::EnterSystem()
{
	cout << "-----------------------------------------------------------------\n";
	cout << "                            전투 입장                           " << endl;
	cout << "-----------------------------------------------------------------\n";
	
	auto player = GSystemContext->GetPlayer(GetSystemType());
	
	// 플레이어 레벨에 따른 monster 생성
	monster = make_shared<Monster>(player->StatManager.get()->GetStat(StatType::Level));
	state = MAINMENU;
}

void BattleSystem::Update()
{
	switch (state)
	{
	case MAINMENU:
		MainMenu();
		break;
	case ATTACK:
		Attack();
		break;
	case DISPLAYSTAT:
		DisplayStat();
		break;
	case USEITEM:
		UseItem();
		break;
	case NEXTSTAGE:
		NextStage();
		break;
	case GAMEOVER:
		GameOver();
		break;
	default:
		break;
	}
}

void BattleSystem::MainMenu()
{
	CLEAR;
	// 라운드 시작할때 몬스터 현재 상태 출력
	monster->StatManager->PrintStatus();

	state = InputManagerSystem::GetInput<int>(
		"==== 전투 메뉴 ====",
		{ "1. 공격하기" , "2. 내 현재 스탯 확인하기","3. 아이템 사용하기" },
		RangeValidator<int>(1, 3)
	);
}

void BattleSystem::Attack()
{
	cout << endl;

	auto player = GSystemContext->GetPlayer(GetSystemType());
	player->Attack(monster.get());

	Delay(1);
	// 몬스터 공격
	cout << endl;
	monster->Attack(player.get());

	Delay(1);
	InputManagerSystem::PauseUntilEnter();

	if (monster->IsDead())
	{
		state = NEXTSTAGE;
	}
	else if (player->IsDead())
	{
		state = GAMEOVER;
	}
	else
	{
		state = MAINMENU;
	}
}

void BattleSystem::DisplayStat()
{
	CLEAR;
	auto player = GSystemContext->GetPlayer(GetSystemType());
	player->StatManager.get()->PrintStatus();

	InputManagerSystem::PauseUntilEnter();

	state = MAINMENU;
}

void BattleSystem::UseItem()
{
	CLEAR;

	auto battleitemcheck = make_shared<IBattleUseItemEvent>();
	GlobalEventManager::Get().Notify(battleitemcheck);
	auto player = GSystemContext->GetPlayer(GetSystemType());
	player->InventoryComponent->displayInventory();
}

void BattleSystem::NextStage()
{
	CLEAR;

	if (monster->IsBoss())
	{// 보스 몬스터
		// 게임 승리 UI 출력
		auto playergameclear = make_shared<IPlayerGameClearEvent>();
		GlobalEventManager::Get().Notify(playergameclear);

		// 게임 승리로 로비로 귀환,
		// 이때까지 동작한 로그라던가는 여기서 출력하시면 됩니다

		auto event = make_shared<IMoveSystemEvent>(SystemType::BATTLE, GetSystemType());
		GlobalEventManager::Get().Notify(event);
		return;
	}
	else
	{	
		// 일반몬스터사망
		// 일반 몬스터 사망 UI 출력
		// 몬스터에게서 보상, 경험치, 돈을 받아서 넘겨주기

		auto player = GSystemContext->GetPlayer(GetSystemType());
		player->InventoryComponent->addGold(monster->CharacterReward.DropGold); // 돈 넣기

		if (monster->CharacterReward.DropItem != nullptr)
		{
			auto playergetitem = make_shared<IPlayerGetItemEvent>();
			GlobalEventManager::Get().Notify(playergetitem);
			player->InventoryComponent->addItem(monster->CharacterReward.DropItem); // 템 넣기
		}

		player->StatManager->ModifyStat(StatType::Experience, 50);
		monster = nullptr;

		auto battlestageclear = make_shared<IPlayerStageClearEvent>();
		GlobalEventManager::Get().Notify(battlestageclear);
		int input = InputManagerSystem::GetInput<int>(
			"==== 스테이지 클리어 메뉴 ====",
			{ "1. 다음 스테이지" , "2. 상점 방문하기" },
			RangeValidator<int>(1, 2)
		);

		if (input == 1)
		{
			EnterSystem();
		}
		else if (input == 2)
		{
			auto event = make_shared<IMoveSystemEvent>(SystemType::SHOP, GetSystemType());
			GlobalEventManager::Get().Notify(event);
		}

		return;
	}
}

void BattleSystem::GameOver()
{
	auto playergamedefeat = make_shared<IPlayerDefeatEvent>();
	GlobalEventManager::Get().Notify(playergamedefeat);

	auto event = make_shared<IMoveSystemEvent>(SystemType::LOBBY, GetSystemType());
	GlobalEventManager::Get().Notify(event);
}