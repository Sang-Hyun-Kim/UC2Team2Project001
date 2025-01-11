#pragma once

#include <iostream>
#include <algorithm>

class IAttackStrategy;
class IDefenseStrategy;

using namespace std;

// 캐릭터(공통 베이스 클래스)
class UStatsComponent;

using namespace std;

class Character 
{

public:
	Character();
	Character(const string& InName);

	virtual ~Character() {}

	virtual void Attack(Character* Target);

	virtual void TakeDamage(int IncomingDamage);

	void SetAttackStrategy(shared_ptr<IAttackStrategy> NewAttackStrategy);

	void SetDefenseStrategy(shared_ptr<IDefenseStrategy> NewDefenseStrategy);

public:
	string CharacterName;

	//스텟 컴포넌트
	shared_ptr<UStatsComponent> StatManager;

protected:
	// 공격/방어 전략 포인터
	shared_ptr<IAttackStrategy> AttackStrategy;
	shared_ptr<IDefenseStrategy> DefenseStrategy;
};

