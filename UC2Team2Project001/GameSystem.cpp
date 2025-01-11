#include "pch.h"
#include "GameSystem.h"

shared_ptr<LobbySystem> GLobbySystem = make_shared<LobbySystem>();
shared_ptr<BattleSystem> GBattleSystem = make_shared<BattleSystem>();

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

void LobbySystem::CreatePlayer()
{
	player = make_unique<Player>("hero",200,5);
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

void LobbySystem::PlayerMove()
{
	GBattleSystem->SetPlayer(this->GetPlayer());
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
