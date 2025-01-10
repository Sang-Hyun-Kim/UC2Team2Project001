#pragma once

#include <iostream>

class IAttackStrategy;
class IDefenseStrategy;

using namespace std;


// 캐릭터(공통 베이스 클래스)
class Character 
{

public:
	Character(const string& InName, int InHP, int InAttack, int InDefense)
		: Name(InName)
		, HP(InHP)
		, AttackPower(InAttack)
		, Defense(InDefense)
		, AttackStrategy(nullptr)
		, DefenseStrategy(nullptr)
	{
		
	}

	virtual ~Character();

	virtual void Attack(Character* Target);

	virtual void TakeDamage(int IncomingDamage);

	bool IsDead() const;

	void PrintStatus() const;
	
	void SetHP(int NewHp) { HP = NewHp; }

	const string& GetName() const { return Name; }
	int GetHP() const { return HP; }
	int GetAttackPower() const { return AttackPower; }
	int GetDefense() const { return Defense; }

	void SetAttackStrategy(IAttackStrategy* NewAttackStrategy);
	
	void SetDefenseStrategy(IDefenseStrategy* NewDefenseStrategy);

protected:
	string Name;
	int HP;
	int AttackPower;
	int Defense;	

	// 공격/방어 전략 포인터
	IAttackStrategy* AttackStrategy;
	IDefenseStrategy* DefenseStrategy;
};


