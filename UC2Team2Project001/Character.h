#pragma once

#include <iostream>
#include <algorithm>

class IAttackStrategy;
class IDefenseStrategy;

using namespace std;

// 캐릭터(공통 베이스 클래스)
class Character 
{

public:
	Character(const string& InName, int InHP, int InMaxHP, int InAttack, int InDefense);

	virtual ~Character() {}

	virtual void Attack(Character* Target);

	virtual void TakeDamage(int IncomingDamage);

	bool IsDead() const;

	void PrintStatus() const;
	
	int SetHP(int NewHp) { HP = NewHp; }
	
	// 현제 체력 변화
	void ChangeHP(int AddHp)
	{
		HP += AddHp;
		
		HP = clamp(HP, 0, MaxHP);
	}

	const string& GetName() const { return Name; }
	int GetHP() const { return HP; }
	int GetMaxHP() const { return MaxHP; }
	int GetAttackPower() const { return AttackPower; }
	int GetDefense() const { return Defense; }

	void SetAttackStrategy(IAttackStrategy* NewAttackStrategy);

	void SetDefenseStrategy(IDefenseStrategy* NewDefenseStrategy);

protected:
	string Name;
	int HP;
	int MaxHP;
	int AttackPower;
	int Defense;

	// 공격/방어 전략 포인터
	IAttackStrategy* AttackStrategy;
	IDefenseStrategy* DefenseStrategy;
};

