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
	cout << "                            ���� ����                           " << endl;
	cout << "-----------------------------------------------------------------\n";
	//�÷��̾� ����
	player = make_shared<Player>("player1", 150,9);
	
	while (!isfinished)
	{
		if (player->GetLevel() >= 10)
		{// 10���� �̻�

		}
		else
		{
			// �ý��ۿ� ����
			CreateMonster();
			cout << monster->GetName() << "�� �����Ǿ����ϴ�.\n";
			isbattlefinished = false;
			// �÷��̾�->���� �ൿ ���� => �Լ�ȭ �ϱ�
			while (!isbattlefinished)
			{
				PrintCommand();
				char command;
				cin >> command;
				switch (command)
				{
				case '1':
					// ���� ȣ��
					// �÷��̾� ���� ó��
					cout << "�÷��̾ ����\n";
					
					// ���� �ǰ� ó��
					monster->SetHp(monster->GetHp() - 50); // 50 ������

					// ���� ��� üũ
					if (monster->isDead())
					{
						cout << "���� óġ!!\n";
						isbattlefinished = true;

						// �÷��̾� ���� ȹ�� ó��
						
						// ����ġ ȹ�� �� �÷��̾� ���� �� ó��

						// ���� ��� ȹ��

						// ���� ������ ȹ��

						// ���� �����

						// �������� ���ƿ��ų� ���� ���� ����

						break;
					}
					
					// ���� ���� ó��
					cout << "���� ����!!\n";
					player->SetHp(player->GetHp() - 20);

					// �÷��̾� ��� ���� ó��
					if (player->isDead())
					{

					}

					break;
				case '2':
					// ��� ȣ��
					// �÷��̾� ��� ó��
					cout << "�÷��̾ ���\n";

					break;
				case '3':
					// ������ ȣ��
					// �÷��̾ ���� ������ ���
					cout << "�÷��̾ ���� ������ ���\n";
					break;
				default:
					cout << "���� ���� �Է��Դϴ�" << endl;
				}
				cin.ignore();
			}// ���� 1ȸ ����
			
		}



	}// ��ü �ý��� ����

	

	cout << "���� �¸�" << endl;
	
	

}

void BattleSystem::CreateMonster()
{
	// ���� ����
	monster = make_shared<Monster>("monster",100);
}

void BattleSystem::PrintCommand()
{
	cout << "�ൿ�� �����ϼ���\n";
	cout << "1. ����\n";
	cout << "2. ���\n";
	cout << "3. ������ ���\n";

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
