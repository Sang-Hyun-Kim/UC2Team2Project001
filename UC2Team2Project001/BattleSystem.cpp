#include "pch.h"
#include "BattleSystem.h"
#include "LobbySystem.h"
#include "ShopSystem.h"
#include "StatComponent.h"
#include "Inventory.h"
#include "PlayerCharacter.h"
#include "Monster.h"
#include "CombatComponent.h"
#include "BattleSystemStates.h"
#include "ICombatEventTypes.h"
#include "IItemEventTypes.h"

BattleSystem::BattleSystem()
{
}

void BattleSystem::EnterSystem()
{
	cout << "-----------------------------------------------------------------\n";
	cout << "                            전투 입장                           " << endl;
	cout << "-----------------------------------------------------------------\n";
	
	auto player = GSystemContext->GetPlayer();
	
	// 플레이어 레벨에 따른 monster 생성
	monster = make_shared<Monster>();
	monster->Initialize();
	state = make_shared<BattleMainState>();
}

//void BattleSystem::ChangeState()
//{
//	if (dynamic_pointer_cast<BattleMainState>(state))
//	{
//		if (currentInput == 1)
//		{
//			state = make_shared<BattleAttackState>();
//		}
//		else if (currentInput == 2)
//		{
//			state = make_shared<BattleDisplayState>();
//		}
//		else
//		{
//			state = make_shared<BattleUseItemState>();
//		}
//	}
//	else if (dynamic_pointer_cast<BattleAttackState>(state))
//	{
//		if (monster->statManager->IsDead())
//		{
//			state = make_shared<BattleNextStageState>();
//		}
//		else if (player->statManager->IsDead())
//		{
//			state = make_shared<BattleGameOverState>();
//		}
//		else
//		{
//			state = make_shared<BattleMainState>();
//		}
//	}
//	else if (dynamic_pointer_cast<BattleUseItemState>(state))
//	{
//		if (currentInput == 0)
//		{
//			state = make_shared<BattleMainState>();
//		}
//	}
//
//}

//void BattleSystem::Update()
//{
//	switch (state)
//	{
//	case MAINMENU:
//		MainMenu();
//		break;
//	case ATTACK:
//		Attack();
//		break;
//	case DISPLAYSTAT:
//		DisplayStat();
//		break;
//	case USEITEM:
//		UseItem();
//		break;
//	case NEXTSTAGE:
//		NextStage();
//		break;
//	case GAMEOVER:
//		GameOver();
//		break;
//	default:
//		break;
//	}
//}

void BattleSystem::MainMenu()
{
	//CLEAR;
	// 라운드 시작할때 몬스터 현재 상태 출력

	

	CharacterUtility::PrintStatus(monster.get());

	int input = InputManagerSystem::GetInput<int>(
		"==== 전투 메뉴 ====",
		{ "1. 공격하기" , "2. 내 현재 스탯 확인하기","3. 아이템 사용하기" },
		RangeValidator<int>(1, 3)
	);

	if (input == 1)
	{
		state = make_shared<BattleAttackState>();
	}
	else if (input == 2)
	{
		state = make_shared<BattleDisplayState>();
	}
	else
	{
		state = make_shared<BattleUseItemState>();
	}
}

void BattleSystem::Attack()
{
	cout << endl;

	auto player = GSystemContext->GetPlayer();
	player->combatManager->SetTarget(monster.get());
	player->combatManager->Attack();
	/*
		플레이어 공격 방식(Active 스킬) 목록 출력 후 선택받기

	CLEAR;

	auto battleitemcheck = make_shared<IBattleAttackEvent>(); // UIEvent로 플레이어 공격 수행 출력
	GlobalEventManager::Get().Notify(battleitemcheck);

	auto player = GSystemContext->GetPlayer(GetSystemType()); // Context로 부터 플레이어 목록 받아오기(System에서 player 저장 x)
	vector<string> ActiveSkillList = player->InventoryComponent->GetInventoryInfoWithString(1);
	// => ItemInventory=>SkillManagerComponent로 변경해서 불러오기
	// => Activeskill header
	int lastIndex = ActiveSkillList.size() + 1; // Add return button

	ActiveSkillList.push_back(to_string(lastIndex) + ". 돌아가기");
	int input = InputManagerSystem::GetInput<int>(
		"==================  스킬 사용 ===================",
		ActiveSkillList,
		RangeValidator<int>(1, lastIndex)
	);

	if (input != lastIndex)
	{
		player->UseItem(input, player.get()); // UseSkill로 변경 예정
		Delay(1);
	}
	*/

	// 몬스터 공격
	cout << endl;
	monster->combatManager->SetTarget(player.get());
	monster->combatManager->Attack();

	InputManagerSystem::PauseUntilEnter();

	if (monster->statManager->IsDead())
	{
		state = make_shared<BattleNextStageState>();
	}
	else if (player->statManager->IsDead())
	{
		state = make_shared<BattleGameOverState>();
	}
	else
	{
		state = make_shared<BattleMainState>();
	}
}

void BattleSystem::DisplayStat()
{
	//CLEAR;
	auto player = GSystemContext->GetPlayer();
	CharacterUtility::PrintStatus(player.get());

	InputManagerSystem::PauseUntilEnter();

	state = make_shared<BattleMainState>();
}

void BattleSystem::UseItem()
{
	CLEAR;

	auto battleitemcheck = make_shared<IBattleUseItemEvent>();
	GlobalEventManager::Get().Notify(battleitemcheck);
	
	auto player = GSystemContext->GetPlayer();
	vector<string> itemList = player->InventoryComponent->GetInventoryInfoWithString(1);
	
	int lastIndex = itemList.size() + 1;

	itemList.push_back(to_string(lastIndex) +". 돌아가기");
	int input = InputManagerSystem::GetInput<int>(
		"=== 아이템 사용 ===", 
		itemList,
		RangeValidator<int>(1, lastIndex)
	);

	if (input != lastIndex)
	{
		player->UseItem(input, player.get());
		Delay(1);
	}
	else state = make_shared<BattleMainState>();
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

		auto event = make_shared<IMoveSystemEvent>(SystemType::LOBBY, GetSystemType());
		GlobalEventManager::Get().Notify(event);
		InputManagerSystem::PauseUntilEnter();
		return;
	}
	else
	{	
		// 일반몬스터 사망
		// 일반 몬스터 사망 UI 출력
		// 몬스터에게서 보상, 경험치, 돈을 받아서 넘겨주기

		auto player = GSystemContext->GetPlayer();
		player->InventoryComponent->addGold(monster->characterReward.DropGold); // 돈 넣기

		if (monster->characterReward.DropItem != nullptr)
		{
			auto playergetitem = make_shared<IPlayerGetItemEvent>();
			GlobalEventManager::Get().Notify(playergetitem);
			player->InventoryComponent->addItem(monster->characterReward.DropItem); // 템 넣기
		}

		CharacterUtility::ModifyStat(player.get(), StatType::Experience, 50);
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

void BattleSystem::OnEvent(const std::shared_ptr<IEvent> ev)
{

}
