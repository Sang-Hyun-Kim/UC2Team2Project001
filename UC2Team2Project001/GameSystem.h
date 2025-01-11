#pragma once
#include "pch.h"
/*
	�׽�Ʈ�� ���� ��¥ �÷��̾�, ����

*/
class Creature;

class Creature
{
public:
	virtual void Attack(shared_ptr<Creature> target) {};
	
	virtual void SetName(string _name);
	virtual string GetName();
	virtual void SetHp(int _hp);
	virtual int GetHp();
	virtual int GetLevel();
	virtual bool isDead() = 0;
protected:
	string name;
	int hp;
	int lvl = 1;
};
class Player : public Creature
{
public:
	Player(string _name, int _hp,int _lvl);
	void Attack(shared_ptr<Creature> target) override;
	virtual bool isDead() override;
};
class Monster : public Creature
{
public:
	Monster(string _name,int _hp);
	void Attack(shared_ptr<Creature> target) override;
	virtual bool isDead() override;
};

class GameSystem
{
public:
	virtual void EnterSystem() {};// �÷��̾ ���� ��ġ���� �Ű� ���� ��� �ش� ���� ������ �����ϴ� �Լ�
	virtual ~GameSystem() {};
	
	virtual void PlayerMove() {}; // �÷��̾��� ���� ��ġ���� �޴� �Լ�
	virtual shared_ptr<Creature> GetPlayer();
	virtual void SetPlayer(shared_ptr<Creature> _player);
protected:
	// �÷��̾� ����
	shared_ptr<Creature> player;
	

};


/*
	�÷��̾��� ����, ���� ����� ���ư��� �κ�
*/
class LobbySystem : public GameSystem 
{
public:
	LobbySystem() {};

	// �÷��̾� ����
	void CreatePlayer();
	//shared_ptr<Player> GetPlayer();
	//void SetPlayer(shared_ptr<Player> _player);
	virtual void PlayerMove() override; // �÷��̾��� ���� ��ġ���� �޴� �Լ�

};

/*
	�÷��̾��� ������ �����ϴ� ����
	Ư�� ��Ȳ�� ���� ������ �κ�� �̵���Ŵ
*/

class BattleSystem : public GameSystem
{
public:
	BattleSystem();
	virtual void EnterSystem() override;
	void CreateMonster();
	void PrintCommand(); // �÷��̾� �ൿ ������ ���
	//shared_ptr<Player> GetPlayer();
	//void SetPlayer(shared_ptr<Player> _player);
	// ���� ��� ���� 
	// ���� ������ ����
	
	// ���� ���� �����
	//



private:
	shared_ptr<Creature> monster;
	bool isbattlefinished = false;
	bool isfinished = false;
};


extern shared_ptr<LobbySystem> GLobbySystem;
extern shared_ptr<BattleSystem> GBattleSystem;
