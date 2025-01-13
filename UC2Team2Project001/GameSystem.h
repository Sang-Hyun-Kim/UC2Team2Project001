#pragma once
#include "pch.h"
#include "Invoker.h"
#include "Monster.h"
/*
	테스트를 위한 가짜 플레이어, 몬스터

*/
//class Creature;
//
//class Creature
//{
//public:
//	virtual void Attack(shared_ptr<Creature> target) {};
//	
//	virtual void SetName(string _name);
//	virtual string GetName();
//	virtual void SetHp(int _hp);
//	virtual int GetHp();
//	virtual int GetLevel();
//	virtual bool isDead() = 0;
//protected:
//	string name;
//	int hp;
//	int lvl = 1;
//};
//class Player : public Creature
//{
//public:
//	Player(string _name, int _hp,int _lvl);
//	void Attack(shared_ptr<Creature> target) override;
//	virtual bool isDead() override;
//};
//class Monster : public Creature
//{
//public:
//	Monster(string _name,int _hp);
//	void Attack(shared_ptr<Creature> target) override;
//	virtual bool isDead() override;
//};

class GameSystem
{
public:
	virtual void EnterSystem() {}; // 시스템이 시작될 때 수행될 함수(Initialize)
	virtual void ExitSystem() {}; // 시스템을 나가야할 때 수행할 함수
	virtual void Update() {}; // system의 로직 수행을 수행하는 함수, 반복
	virtual ~GameSystem() {};

	virtual void PlayerMove(shared_ptr<GameSystem> next); // 플레이어의 이전 위치에서 받는 함수

	virtual shared_ptr<Character> GetPlayer();
	virtual void SetPlayer(shared_ptr<Character> _player);
protected:
	// 플레이어 저장
	shared_ptr<Character> player;
	shared_ptr<GameSystem> nextsystem;

};


/*
	플레이어의 생성, 게임 종료시 돌아가는 로비
*/
class LobbySystem : public GameSystem 
{
public:
	LobbySystem() {};
	void EnterSystem() override; // 로비 실행후 동작
	virtual void ExitSystem();
	virtual void Update();
	void CreatePlayer();
	//shared_ptr<Player> GetPlayer();
	//void SetPlayer(shared_ptr<Player> _player);

	bool isValidName(const string& _username); // 유저 이름 검색

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
	virtual void ExitSystem();
	virtual void Update();
	void CreateMonster();

	//shared_ptr<Player> GetPlayer();
	//void SetPlayer(shared_ptr<Player> _player);
	
	// 랜덤 골드 생성 
	// 랜덤 아이템 생성
	
	// 상점 진입 물어보기

private:
	shared_ptr<Monster> monster;
	bool isbattlefinished = false;
	bool isfinished = false;
};

class SystemContext
{
public:

	shared_ptr<GameSystem> currentSystem = nullptr;

	void RunSystem(shared_ptr<GameSystem> next); // 다음 실행될 EnterSystem이 실행될 정보 정해주기
	void MoveSystem(shared_ptr<GameSystem> to, shared_ptr<GameSystem> from); // 이전 시스템-> 다음 시스템으로 플레이어 메모리 이동
		
};
extern shared_ptr<SystemContext> GSystemContext;
extern shared_ptr<LobbySystem> GLobbySystem;
extern shared_ptr<BattleSystem> GBattleSystem;
