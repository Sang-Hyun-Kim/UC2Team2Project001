#include "pch.h"
#include "GameSystem.h"
#include "InputManagerSystem.h"
#include "ShopSystem.h"
#include "StatComponent.h"
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
	
	// 플레이어 레벨에 따른 monster 생성
	monster = make_shared<Monster>(player->StatManager.get()->GetStat(StatType::Level));

	// 전투시작
	cout << "전투 커맨드:";
	char command;
	
	// 목표
	/*while ()
	{
		update()
	}*/

	while (!player->IsDead() && !monster->IsDead())
	{
		cin >> command;
		switch (command)
		{
		case '1':
			// 공격
			// 플레이어 공격(몬스터) 	// 몬스터 사망 검증
			cout << "플레이어 공격 수행" << endl;
			player->Attack(monster.get());
			// 몬스터 사망시
			// IsBoss 분기
			//// 게임승리
			//// 전투, 상점 선택지

			// 몬스터 공격
			monster->Attack(player.get());
			// 플레이어 사망 검증
			// 로비 되돌아 가기

			break;
		case '2':
			// 현재 상태 출력
			player->StatManager.get()->PrintStatus();
			break;
		case '3':
			// 아이템 사용

			break;
		default:
			break;
		}

	}
	
	char scommand;

	cout << "상점가기 1 2 " << endl;
	cin >> scommand;
	switch (scommand)
	{

	case '1':
		// 상점 가기	
		GSystemContext->RunSystem(GShopSystem);
		GSystemContext->MoveSystem(GShopSystem, GBattleSystem); // Lobby->Battle
		break;
	case '2':
		// 다시 전투 하기
		GSystemContext->RunSystem(GBattleSystem);
		GSystemContext->MoveSystem(GBattleSystem, GLobbySystem); // Lobby->Battle

		break;
	default:
		break;
	}

	


}

//void BattleSystem::CreateMonster()
//{
//	// 몬스터 제작
//	monster = make_shared<Monster>("monster",100);
//}

//void BattleSystem::PrintCommand()
//{
//	cout << "행동을 선택하세요\n";
//	cout << "1. 공격\n";
//	cout << "2. 방어\n";
//	cout << "3. 아이템 사용\n";
//
//}

//shared_ptr<Player> BattleSystem::GetPlayer()
//{
//}
//
//void BattleSystem::SetPlayer(shared_ptr<Player> _player)
//{
//	player = _player;
//}



void LobbySystem::EnterSystem()
{
	int input = InputManagerSystem::GetInput<int>(
		" 게임 로비 메뉴를 출력합니다.",
		{ "1. 게임 시작" , "2. 게임 종료"},
		RangeValidator<int>(1, 2)
	);
	if (input == 1)
	{
		auto gamestart = make_shared<IGameStartEvent>();
		GlobalEventManager::Get().Notify(gamestart); 
		CreatePlayer();
	}
	else if (input == 2)
	{
		auto gamexit = make_shared<IGameExitEvent>();
		GlobalEventManager::Get().Notify(gamexit);
	}
}


void LobbySystem::CreatePlayer()
{
	cout << "캐릭터를 생성합니다.\n";
	bool chnamevalid = false;
	string username;
	while (!chnamevalid)
	{
		cout << "캐릭터의 이름을 입력해주세요.\n";
		cout << "이름(중간 공백 허용, 최대12자): ";

		cin.ignore();
		getline(cin,username);
		chnamevalid = isValidName(username);
	}

	player = make_shared<Character>("Player");
	// 캐릭터를 생성하고 statecontext를 BattleSystem으로 넘김
	// 다음 system->EnterSystem()이 battlesystem으로 실행됨

	GSystemContext->RunSystem(GBattleSystem);
	GSystemContext->MoveSystem(GBattleSystem, GLobbySystem); // Lobby->Battle
}

//shared_ptr<Player> LobbySystem::GetPlayer()
//{
//	return player;
//}
//
//void LobbySystem::SetPlayer(shared_ptr<Player> _player)
//{
//	
//}

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

void GameSystem::PlayerMove(shared_ptr<GameSystem> next)
{
	next->SetPlayer(this->GetPlayer());
	this->SetPlayer(nullptr);
}

shared_ptr<Character> GameSystem::GetPlayer()
{
	return player;
}

void GameSystem::SetPlayer(shared_ptr<Character> _player)
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
	from->PlayerMove(to);

}
