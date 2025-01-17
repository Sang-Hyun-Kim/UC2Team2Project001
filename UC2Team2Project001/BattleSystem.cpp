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
#include "UIEventManagerSystem.h"
#include "IItemEventTypes.h"
#include "USkillComponent.h"
#include "URewardEventManagerSystem.h"
#include "SkillManager.h"
#include "Skill.h"
#include "UTurnEventManager.h"
#include "ICharacterEventTypes.h"

#include "Invoker.h"
#include "CommandTypes.h"
#include "ConsoleLayout.h"

BattleSystem::BattleSystem()
{
	rewardSystem = make_shared<URewardEventManagerSystem>();
	GlobalEventManager::Get().Subscribe(rewardSystem);

	turnSystem = std::make_shared<UTurnEventManager>();
	GlobalEventManager::Get().Subscribe(turnSystem);
}

void BattleSystem::EnterSystem()
{
	//cout << "-----------------------------------------------------------------\n";
	//cout << "                            전투 입장                           " << endl;
	//cout << "-----------------------------------------------------------------\n";
	//CLEAR;
	auto player = GSystemContext->GetPlayer();
	monster = make_shared<Monster>();
	monster->Initialize();
	monster->combatManager->SetTarget(player.get());
	player->combatManager->SetTarget(monster.get());

	player->combatManager->SetTarget(monster.get());

	activeCharacters.clear();
	activeCharacters.push_back(player.get());
	activeCharacters.push_back(monster.get());
	
	// 플레이어 레벨에 따른 monster 생성
	state = make_shared<BattleMainState>();

	rewardSystem->Initialize();
	turnSystem->TurnReset();
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

void BattleSystem::MainMenu()
{
	// 라운드 시작할때 몬스터 현재 상태 출력
	DisplayStat();



	int input = InputManagerSystem::GetInput<int>(
		"==== 전투 메뉴 ====",
		{ "1. 공격하기" ,"2. 아이템 사용하기" },
		RangeValidator<int>(1, 2)
	);

	if (input == 1)
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<BattleAttackState>());
		GInvoker->ExecuteCommand(cmd);
		//state = make_shared<BattleAttackState>();
	}
	else
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<BattleUseItemState>());
		GInvoker->ExecuteCommand(cmd);
		//state = make_shared<BattleUseItemState>();
	}
}

void BattleSystem::Attack()
{
	auto battleitemcheck = make_shared<IPlayerBattleAttackEvent>(); // UIEvent로 플레이어 공격 수행 출력
	GlobalEventManager::Get().Notify(battleitemcheck);

	auto player = GSystemContext->GetPlayer();

	vector<string> activeSkillList = player->skillManager->GetActiveSkillInfoWithString(0);
	// Context로 부터 플레이어 목록 받아오기(System에서 player 저장 x)
	// 1~n: 가지고 있는 스킬
	// n+1: 일반공격
	// n+2: 돌아가기
	// 스킬이 아예 없는경우, 1. 일반공격, 2. 돌아가기
	// 스킬이 하나인 경우 1. 스킬1, 2. 일반 공격, 3. 돌아가기
	int returnButton = activeSkillList.size() + 1; // 일반 공격


	activeSkillList.push_back(to_string(returnButton) + ". 돌아가기");

	int input = InputManagerSystem::GetInput<int>(
		"==================  스킬 사용 ===================",
		activeSkillList,
		RangeValidator<int>(1, returnButton)
	);

	if (input == returnButton)
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<BattleMainState>());
		GInvoker->ExecuteCommand(cmd);
		//state = make_shared<BattleMainState>();
		return; // mainstate 재실행=>공격,스탯,아이템 메뉴 재실행
	}
	else
	{ // 스킬 사용
		//CLEAR;
		//auto cmd = make_shared<UseSkillCommand>(player->skillManager->GetActiveSkillNameByIndex(input - 1));
		//GInvoker->ExecuteCommand(cmd);
		//player->skillManager->UseSkill(SkillType::ACTIVE, player->skillManager->GetActiveSkillNameByIndex(input - 1)); // UseSkill로 변경 예정
		//player->skillManager->UseSkill(input - 1);
		//Delay(1);

		auto playerAttackEv = make_shared<IPlayerBattleAttackEvent>();
		GlobalEventManager::Get().Notify(playerAttackEv);

		auto player = GSystemContext->GetPlayer();

		state = make_shared<BattleMainState>();
		
		if (!player->skillManager->UseSkill(player->skillManager->GetActiveSkillNameByIndex(input - 1)))
		{
			state = make_shared<BattleMainState>();
			return;
		}
	}

	// 몬스터 공격
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "\n");
	monster->combatManager->SetTarget(player.get());

	auto monsterAttackEv = make_shared<IMonsterBattleAttackEvent>();
	GlobalEventManager::Get().Notify(monsterAttackEv);

	monster->skillManager->UseSkill("기본 공격");// 몬스터 죽으면 공격 안함
	
	turnSystem->EndTurn(activeCharacters);

	DisplayStat();

	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "\n");

	InputManagerSystem::PauseUntilEnter();
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);
}

void BattleSystem::DisplayStat()
{
	//CLEAR;
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftTop);
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::RightTop);
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftTop);
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::RightTop);

	auto player = GSystemContext->GetPlayer();
	player.get()->PrintCharacterInfo();
	monster.get()->PrintCharacterInfo(1);
}

void BattleSystem::UseItem()
{
	//CLEAR;

	auto battleitemcheck = make_shared<IBattleUseItemEvent>();
	GlobalEventManager::Get().Notify(battleitemcheck);
	
	auto player = GSystemContext->GetPlayer();
	vector<string> itemList = player->inventoryComponent->GetInventoryInfoWithString(1);
	
	int lastIndex = itemList.size() + 1;

	itemList.push_back(to_string(lastIndex) +". 돌아가기");
	int input = InputManagerSystem::GetInput<int>(
		"=== 아이템 사용 ===", 
		itemList,
		RangeValidator<int>(1, lastIndex)
	);

	if (input != lastIndex)
	{
		auto cmd = make_shared<UseItemCommand>(input - 1);
		GInvoker->ExecuteCommand(cmd);
		Delay(1);
	}
	else state = make_shared<BattleMainState>();
}

void BattleSystem::NextStage()
{
	//CLEAR;

	if (monster->IsBoss())
	{	
		// 보스 몬스터
		// 게임 승리 UI 출력
		auto playergameclear = make_shared<IPlayerGameClearEvent>();
		GlobalEventManager::Get().Notify(playergameclear);

		// 게임 승리로 로비로 귀환,
		// 이때까지 동작한 로그라던가는 여기서 출력하시면 됩니다

		auto event = make_shared<IMoveSystemEvent>(SystemType::LOBBY, GetSystemType(), "로비", "배틀");
		GlobalEventManager::Get().Notify(event);
		InputManagerSystem::PauseUntilEnter();
		ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);
		return;
	}
	else
	{	
		GetReward();

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
			auto cmd = make_shared<SystemMoveCommand>(SystemType::SHOP, GetSystemType(), "상점", "배틀");
			GInvoker->ExecuteCommand(cmd);
		}
	}
}

void BattleSystem::GameOver()
{
	auto playergamedefeat = make_shared<IPlayerDefeatEvent>();
	GlobalEventManager::Get().Notify(playergamedefeat);

	auto event = make_shared<IMoveSystemEvent>(SystemType::LOBBY, GetSystemType(), "로비", "배틀");
	GlobalEventManager::Get().Notify(event);
}

void BattleSystem::StartTurn()
{
	//CLEAR;
	//turnSystem->BeginTurn();
	//cout << "\n\n";
	//state = make_shared<BattleMainState>();
}

void BattleSystem::OnEvent(const std::shared_ptr<IEvent> _event)
{
	if (auto deadEvent = dynamic_pointer_cast<ICharacterDeadEvent>(_event))
	{
		auto player = GSystemContext->GetPlayer();
		if (monster->statManager->IsDead())
		{
			state = make_shared<BattleNextStageState>();
		}
		else if (player->statManager->IsDead())
		{
			state = make_shared<BattleGameOverState>();
		}
	}
	else if (auto turnEvent = dynamic_pointer_cast<ITurnStartEvent>(_event))
	{
		turnSystem->BeginTurn();
	}
}

void BattleSystem::GetReward()
{
	auto player = GSystemContext->GetPlayer();
	auto reward = rewardSystem->GetReward();

	player->inventoryComponent->addGold(reward.gold); // 돈 넣기

	if (monster->characterReward.dropItem != nullptr)
	{
		auto playergetitem = make_shared<IPlayerGetItemEvent>();
		GlobalEventManager::Get().Notify(playergetitem);
		player->inventoryComponent->addItem(reward.item); // 템 넣기
	}

	int skillSize = reward.skillTypes.size();
	
	if (reward.skillTypes.size() > 0)
	{
		vector<string> options;

		for (int i = 0; i < skillSize; i++)
		{
			shared_ptr<Skill> skill = SkillManager::GetInstance().CreateSkillFromType(reward.skillTypes[i], player.get());
			options.push_back(to_string(i + 1) + ", " + skill->GetSkillData().skillName);
		}

		int input = InputManagerSystem::GetInput<int>("=== 스킬 선택 ===", options, RangeValidator<int>(1, reward.skillTypes.size()));

		auto cmd = make_shared<AddSkillCommand>(reward.skillTypes[input - 1]);
		GInvoker->ExecuteCommand(cmd);
		Delay(1);
		//SkillManager::GetInstance().AddSelectSkillToCharacter(reward.skillTypes[input], player.get());
	}

	CharacterUtility::ModifyStat(player.get(), StatType::Experience, rewardSystem->GetReward().exp);
	monster = nullptr;

	auto battlestageclear = make_shared<IPlayerStageClearEvent>();
	GlobalEventManager::Get().Notify(battlestageclear);
}