#include "pch.h"
#include "GameSystem.h"
#include "InputManagerSystem.h"
#include "ShopSystem.h"
#include "StatComponent.h"
#include "PlayerCharacter.h"
#include "Inventory.h"
shared_ptr<LobbySystem> GLobbySystem = make_shared<LobbySystem>();
shared_ptr<BattleSystem> GBattleSystem = make_shared<BattleSystem>();
shared_ptr<SystemContext> GSystemContext = make_shared<SystemContext>();
BattleSystem::BattleSystem()
{
}

void BattleSystem::EnterSystem()
{
	cout << "-----------------------------------------------------------------\n";
	cout << "                            전투 입장                           " << endl;
	cout << "-----------------------------------------------------------------\n";
	
	//플레이어 검증
	if (player == nullptr)
	{
		// 플레이어 제대로 안넘어옴
		cout << "플레이어 nullptr" << endl;

	}

	// 플레이어 레벨에 따른 monster 생성
	monster = make_shared<Monster>(player->StatManager.get()->GetStat(StatType::Level));

}

void BattleSystem::Update()
{
	// 이번 라운드 시작 전 검증
	// 플레이어 사망 여부
	if (player->IsDead())
	{
		// 로비 귀환 UI 출력
		auto playergamedefeat = make_shared<IPlayerDefeatEvent>();
		GlobalEventManager::Get().Notify(playergamedefeat);
		ExitSystem(GLobbySystem);
		return;
	}

	if (monster->IsDead())
	{

		if (monster->IsBoss()) 
		{// 보스 몬스터
			// 게임 승리 UI 출력
			auto playergameclear = make_shared<IPlayerGameClearEvent>();
			GlobalEventManager::Get().Notify(playergameclear);

			// 게임 승리로 로비로 귀환,
			// 이때까지 동작한 로그라던가는 여기서 출력하시면 됩니다


			ExitSystem(GLobbySystem);
			return;
		}
		else
		{// 일반몬스터사망
			// 일반 몬스터 사망 UI 출력
			// 몬스터에게서 보상, 경험치, 돈을 받아서 넘겨주기
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
				" 스테이지 클리어 메뉴",
				{ "1. 다음 스테이지" , "2. 상점 방문하기"},
				"input: ",
				RangeValidator<int>(1, 2)
			);
			if (input == 1)
			{
				// 다음 스테이지
				ExitSystem(GBattleSystem);
			}
			else if (input == 2)
			{
				// 상점 가기
				ExitSystem(GShopSystem);
			}
			return;
		}
	
	}
	
	// 라운드 시작할때 몬스터 현재 상태 출력
	monster->StatManager->PrintStatus();
	int input = InputManagerSystem::GetInput<int>(
		" 전투 메뉴",
		{ "1. 공격하기" , "2. 내 현재 스탯 확인하기","3. 아이템 사용하기"},
		"input: ",
		RangeValidator<int>(1, 3)
	);
	if (input == 1) // 공격
	{
		auto battleplayerattack = make_shared<IBattleAttackEvent>();
		GlobalEventManager::Get().Notify(battleplayerattack);

		player->Attack(monster.get());
		// 공격
		// 플레이어 공격(몬스터) 	// 몬스터 사망 검증

		// 몬스터 사망시
		// IsBoss 분기
		//// 게임승리
		//// 전투, 상점 선택지

		// 몬스터 공격
		monster->Attack(player.get());
		// 플레이어 사망 검증
		// 로비 되돌아 가기
	}
	else if (input == 2) // 스탯
	{
		auto battlestatCheck = make_shared<IBattleStatCheckEvent>();
		GlobalEventManager::Get().Notify(battlestatCheck);
		player->StatManager.get()->PrintStatus();
	}
	else if (input == 3) // 아이템
	{
		auto battleitemcheck = make_shared<IBattleUseItemEvent>();
		GlobalEventManager::Get().Notify(battleitemcheck);
		player->InventoryComponent->displayInventory();
		if (!player->InventoryComponent->IsEmpty())
		{
			int idx = InputManagerSystem::GetInput<int>(
				"돌아가기는 q를 입력해주세요",
				{  },
				"input: ",
				NoValidator<int>()
			);
			player->UseItem(idx,dynamic_pointer_cast<Character>(player).get());
		}
		
	}

}


void LobbySystem::EnterSystem()
{
	// 처음 로비에 들어왔을 때
	// 게임 시작, 또는 게임 패배 후 돌아왔을 때
	// 지금 굳이 필요 없는 기능, 추후 확장=> 로비가 시작되었을 때 해야하는 것들
	// 로그인, 로그인 검증 등
}

void LobbySystem::Update()
{
	int input = InputManagerSystem::GetInput<int>(
		" 게임 로비 메뉴를 출력합니다.",
		{ "1. 게임 시작" , "2. 게임 종료" },
		"input: ",
		RangeValidator<int>(1, 2)
	);
	if (input == 1)
	{
		auto gamestart = make_shared<IGameStartEvent>();
		GlobalEventManager::Get().Notify(gamestart);
		
		// 캐릭터를 생성하고 statecontext를 BattleSystem으로 넘김
		// 다음 system->EnterSystem()이 battlesystem으로 실행됨
		CreatePlayer();
		GSystemContext->currentSystem->ExitSystem(GBattleSystem);
	}
	else if (input == 2)
	{
		auto gamexit = make_shared<IGameExitEvent>();
		GlobalEventManager::Get().Notify(gamexit);
	}

}

void LobbySystem::CreatePlayer()
{
	cout << endl;
	string username = InputManagerSystem::GetInput(
		"캐릭터의 이름을 입력해주세요.",
		{ "이름(중간 공백 허용, 최대12자): " },
		"input: ",
		NameRangeValidator(1, 12),
		NameSpaceValidator(),
		RegexValidator("이름에 특수문자가 포함되어 있습니다.")
	);
//	추후 Player의 displayname을 username 값으로 사용해주세요!!
	cout << "입력된 플레이어 캐릭터 이름은 "<<username <<" 입니다." <<endl;
	player = make_shared<Player>("Player");


}

bool LobbySystem::isValidName(const string& _username)
{
	//if (_username.size() > 12)
	//{
	//	cout << "이름 사이즈 초과. 다시 입력하세요" << endl;
	//	return false;
	//}
	//if (_username.empty()) {
	//	cout << "이름을 입력하지 않으셨습니다. 다시 입력하세요" << endl;
	//	return false;
	//}
	//if (std::all_of(_username.begin(), _username.end(), std::isspace))
	//{
	//	cout << "전부 공백만 입력하셨습니다. 다시 입력하세요" << endl;
	//	return false;
	//}

	//// 알파벳,숫자, 공백이아닌 특수문자의 경우 실패 반환
	//for (char ch : _username) 
	//{
	//	if (!std::isspace(ch) && !std::isalnum(ch))
	//	{
	//		cout << "특수 문자는 허용되지 않습니다. 다시 입력하세요." << endl;
	//		return false;
	//	}
	//}
	return true;
}

void GameSystem::ExitSystem(shared_ptr<GameSystem> next)
{
	GSystemContext->MoveSystem(next, GSystemContext->currentSystem); // Lobby->Battle
	GSystemContext->RunSystem(next);
	GSystemContext->currentSystem->EnterSystem();
}

void GameSystem::PlayerMove(shared_ptr<GameSystem> next)
{
	next->SetPlayer(this->GetPlayer());
	
	this->SetPlayer(nullptr);
}

shared_ptr<Player> GameSystem::GetPlayer()
{
	return player;
}

void GameSystem::SetPlayer(shared_ptr<Player> _player)
{
	player = _player;
}

void SystemContext::RunSystem(shared_ptr<GameSystem> next)
{
	currentSystem = next; // 다음 EnterSystem을 실행할 System 입력
}

void SystemContext::MoveSystem(shared_ptr<GameSystem> to, shared_ptr<GameSystem> from)
{
	// System from 에서 System to 로 이동
	if(to != from)
		from->PlayerMove(to);

}
