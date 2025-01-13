#include "pch.h"
#include "GameSystem.h"
#include "InputManagerSystem.h"

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
	if (player == nullptr)
	{
		cout << "nullptr\n";
	}
	else
	{
		cout << "not nullptr\n";
	}
	cout << "플레이어 " << player->GetName() << "이 전투를 시작합니다!" << endl;
	cout << "게임 승리" << endl;
	
	

}

void BattleSystem::CreateMonster()
{
	// 몬스터 제작
	monster = make_shared<Monster>("monster",100);
}

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

Player::Player(string _name, int _hp,int _lvl)
{
	this->name = _name;
	this->hp = _hp;
	this->lvl = _lvl;
}

void Player::Attack(shared_ptr<Creature> target)
{
	
}

bool Player::isDead()
{
	if (hp <= 0)
		return true;
	else
		return false;
}

Monster::Monster(string _name, int _hp)

{
	SetName(_name);
	this->hp = _hp;

}

void Monster::Attack(shared_ptr<Creature> target)
{
}

bool Monster::isDead()
{
	if (hp <= 0)
		return true;
	else
		return false;
}

void Creature::SetName(string _name)
{
	name = _name;
}

string Creature::GetName()
{
	return name;
}

void Creature::SetHp(int _hp)
{
	hp = _hp;
}

int Creature::GetHp()
{
	return hp;
}

int Creature::GetLevel()
{
	return lvl;
}

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

	player = make_shared<Player>(username,200,5);
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
	if (_username.size() > 12)
	{
		cout << "이름 사이즈 초과. 다시 입력하세요" << endl;
		return false;
	}
	if (_username.empty()) {
		cout << "이름을 입력하지 않으셨습니다. 다시 입력하세요" << endl;
		return false;
	}
	if (std::all_of(_username.begin(), _username.end(), isspace))
	{
		cout << "전부 공백만 입력하셨습니다. 다시 입력하세요" << endl;
		return false;
	}

	// 알파벳,숫자, 공백이아닌 특수문자의 경우 실패 반환
	for (char ch : _username) 
	{
		if (!std::isspace(ch) && !std::isalnum(ch))
		{
			cout << "특수 문자는 허용되지 않습니다. 다시 입력하세요." << endl;
			return false;
		}
	}
	return true;
}

void GameSystem::PlayerMove(shared_ptr<GameSystem> next)
{
	next->SetPlayer(this->GetPlayer());
	this->SetPlayer(nullptr);
}

shared_ptr<Creature> GameSystem::GetPlayer()
{
	return player;
}

void GameSystem::SetPlayer(shared_ptr<Creature> _player)
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
