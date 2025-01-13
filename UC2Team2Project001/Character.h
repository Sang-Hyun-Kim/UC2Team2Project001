#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include "CharacterTypes.h"

class IAttackStrategy;
class IDefenseStrategy;
class Item;

struct StatsData;

using namespace std;

// 캐릭터(공통 베이스 클래스)
class UStatsComponent;

using namespace std;

class Character 
{

public:
	//생성자 및 소멸자
	Character();

	Character(const string& InName);

public:
	void Initialize(const StatsData& stats);

	virtual ~Character() {}

	// 공격 및 피해 처리
	virtual void Attack(Character* Target);
	virtual void TakeDamage(int IncomingDamage);

	// 전략 설정
	void SetAttackStrategy(shared_ptr<IAttackStrategy> NewAttackStrategy);

	void SetDefenseStrategy(shared_ptr<IDefenseStrategy> NewDefenseStrategy);

	virtual void CreateCharacterReward() {}

	virtual void UseItem(const string& ItemName);

public:
	bool IsDead();

	// 캐릭터 이름 반환
	const string& GetName() { return CharacterName; }

public:

	//스텟 컴포넌트
	shared_ptr<UStatsComponent> StatManager;

protected:
	// 공격/방어 전략
	shared_ptr<IAttackStrategy> AttackStrategy;
	shared_ptr<IDefenseStrategy> DefenseStrategy;

public:
	
	// 캐릭터 사망 보상
	FCharacterReward CharacterReward;

protected:
	string CharacterName;
};


