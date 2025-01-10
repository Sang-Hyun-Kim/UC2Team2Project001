#include "pch.h"
#include <memory>
#include "Character.h"
#include "IStrategy.h"
#include "StatusComponent.h"
#include "StatComponent.h"


Character::Character(const string& InName, int InHP, int InMaxHP, int InAttack, int InDefense)
	: CharacterName(InName), AttackStrategy(nullptr), DefenseStrategy(nullptr)
{
	StatusManager = make_shared<StatusComponent>();
	StatManager = make_shared<UStatsComponent>(this);
}

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

	StatManager->ModifyStat(StatType::HP, (float)finalDamage);
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
