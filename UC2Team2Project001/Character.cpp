#include "pch.h"
#include "Character.h"
#include "IStrategy.h"

void Character::Attack(Character* Target)
{
	if (!Target || !AttackStrategy)
	{
		cout << "타겟이 없거나 공격 어택이 없습니다";
		return;
	}

	AttackStrategy->Attack(this, Target);
}

void Character::TakeDamage(int IncomingDamage)
{
	int finalDamage = IncomingDamage;

	if (DefenseStrategy)
	{
		finalDamage = DefenseStrategy->CalculateDamageReceived(this, IncomingDamage);
	}

	HP -= finalDamage;
	if (HP < 0)
		HP = 0;

	//ToDo: 나중에 OnDead 콜백을 만들어줄 예정
	//콜백을 리워드 시스템에 연결
}

bool Character::IsDead() const
{
	return (HP <= 0);
}

void Character::PrintStatus() const
{
	std::cout << "[ " << Name << " ] HP: " << HP
		<< " / ATK: " << AttackPower
		<< " / DEF: " << Defense << std::endl;
}

void Character::SetAttackStrategy(IAttackStrategy* NewAttackStrategy)
{
	delete AttackStrategy;
	AttackStrategy = NewAttackStrategy;
}

void Character::SetDefenseStrategy(IDefenseStrategy* NewDefenseStrategy)
{
	delete DefenseStrategy;
	DefenseStrategy = NewDefenseStrategy;
}
