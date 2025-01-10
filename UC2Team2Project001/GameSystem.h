#pragma once
#include "pch.h"
/*
	테스트를 위한 가짜 플레이어, 몬스터

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
	virtual void EnterSystem() {};// 플레이어가 이전 위치에서 옮겨 졌을 경우 해당 방의 로직을 실행하는 함수
	virtual ~GameSystem() {};
	
	virtual void PlayerMove() {}; // 플레이어의 이전 위치에서 받는 함수
	virtual shared_ptr<Player> GetPlayer();
	virtual void SetPlayer(shared_ptr<Player> _player);
protected:
	// 플레이어 저장
	shared_ptr<Player> player;
	

};


/*
	플레이어의 생성, 게임 종료시 돌아가는 로비
*/
class LobbySystem : public GameSystem 
{
public:
	LobbySystem() {};

	// 플레이어 생성
	void CreatePlayer();
	//shared_ptr<Player> GetPlayer();
	//void SetPlayer(shared_ptr<Player> _player);
	virtual void PlayerMove() override; // 플레이어의 이전 위치에서 받는 함수

};

/*
	플레이어의 전투를 진행하는 공간
	특정 상황에 따라 상점과 로비로 이동시킴
*/

class BattleSystem : public GameSystem
{
public:
	BattleSystem();
	virtual void EnterSystem() override;
	void CreateMonster();
	void PrintCommand(); // 플레이어 행동 선택지 출력
	//shared_ptr<Player> GetPlayer();
	//void SetPlayer(shared_ptr<Player> _player);
	// 랜덤 골드 생성 
	// 랜덤 아이템 생성
	
	// 상점 진입 물어보기
	//



private:
	shared_ptr<Creature> monster;
	shared_ptr<Creature> player;
	bool isbattlefinished = false;
	bool isfinished = false;
};


extern shared_ptr<LobbySystem> GLobbySystem;
extern shared_ptr<BattleSystem> GBattleSystem;
