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
	//플레이어 생성
	player = make_shared<Player>("player1", 150,9);
	
	while (!isfinished)
	{
		if (player->GetLevel() >= 10)
		{// 10레벨 이상

		}
		else
		{
			// 시스템에 몬스터
			CreateMonster();
			cout << monster->GetName() << "이 생성되었습니다.\n";
			isbattlefinished = false;
			// 플레이어->몬스터 행동 루프 => 함수화 하기
			while (!isbattlefinished)
			{
				PrintCommand();
				char command;
				cin >> command;
				switch (command)
				{
				case '1':
					// 공격 호출
					// 플레이어 공격 처리
					cout << "플레이어가 공격\n";
					
					// 몬스터 피격 처리
					monster->SetHp(monster->GetHp() - 50); // 50 때리기

					// 몬스터 사망 체크
					if (monster->isDead())
					{
						cout << "몬스터 처치!!\n";
						isbattlefinished = true;

						// 플레이어 보상 획득 처리
						
						// 경험치 획득 및 플레이어 레벨 업 처리

						// 랜덤 골드 획득

						// 랜덤 아이템 획득

						// 상점 물어보기

						// 상점에서 돌아오거나 다음 전투 진행

						break;
					}
					
					// 몬스터 공격 처리
					cout << "몬스터 공격!!\n";
					player->SetHp(player->GetHp() - 20);

					// 플레이어 사망 판정 처리
					if (player->isDead())
					{

					}

					break;
				case '2':
					// 방어 호출
					// 플레이어 방어 처리
					cout << "플레이어가 방어\n";

					break;
				case '3':
					// 아이템 호출
					// 플레이어가 가진 아이템 출력
					cout << "플레이어가 가진 아이템 출력\n";
					break;
				default:
					cout << "옳지 않은 입력입니다" << endl;
				}
				cin.ignore();
			}// 전투 1회 루프
			
		}



	}// 전체 시스템 루프

	

	cout << "게임 승리" << endl;
	
	

}

void BattleSystem::CreateMonster()
{
	// 몬스터 제작
	monster = make_shared<Monster>("monster",100);
}

void BattleSystem::PrintCommand()
{
	cout << "행동을 선택하세요\n";
	cout << "1. 공격\n";
	cout << "2. 방어\n";
	cout << "3. 아이템 사용\n";

}

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

shared_ptr<Player> GameSystem::GetPlayer()
{
	return dynamic_pointer_cast<Player>(player);
}

void GameSystem::SetPlayer(shared_ptr<Player> _player)
{
	player = _player;
}
