#include "pch.h"
#include "Character.h"
#include "IStrategy.h"
#include "IEventTypes.h"
#include "GlobalEventManager.h"

Character::~Character()
{
	delete AttackStrategy;
	delete DefenseStrategy;
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

	HP -= finalDamage;

	//
	auto DamageEvent = std::make_shared<ICharacterDamagedEvent>(Name,finalDamage);
	GlobalEventManager::Get().Notify(DamageEvent);


	if (HP < 0)
	{
		HP = 0;
		auto DeadEvent = std::make_shared<ICharacterDeadEvent>(Name);
		GlobalEventManager::Get().Notify(DeadEvent);
	}

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
