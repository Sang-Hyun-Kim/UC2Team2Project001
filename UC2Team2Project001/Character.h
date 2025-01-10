#pragma once

#include <iostream>
#include <algorithm>

class IAttackStrategy;
class IDefenseStrategy;
class StatusComponent;
class UStatsComponent;

using namespace std;


class Character 
{

public:
	Character(const string& InName, int InHP, int InMaxHP, int InAttack, int InDefense);

	virtual ~Character() {}

	virtual void Attack(Character* Target);

	virtual void TakeDamage(int IncomingDamage);

	void SetAttackStrategy(IAttackStrategy* NewAttackStrategy);

	void SetDefenseStrategy(IDefenseStrategy* NewDefenseStrategy);

public:
	string CharacterName;

	//스텟 컴포넌트
	shared_ptr<UStatsComponent> StatManager;

protected:
	// 공격/방어 전략 포인터
	IAttackStrategy* AttackStrategy;
	IDefenseStrategy* DefenseStrategy;

	//상태 컴포넌트
	shared_ptr<StatusComponent> StatusManager;

};

