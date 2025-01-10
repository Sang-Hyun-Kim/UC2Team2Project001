#include "pch.h"
#include <memory>
#include "Character.h"
#include "IStrategy.h"
#include "IEventTypes.h"
#include "GlobalEventManager.h"


Character::Character(const string& InName, int InHP, int InMaxHP, int InAttack, int InDefense)
	: Name(InName)
	, HP(InHP)
	, MaxHP(InMaxHP)
	, AttackPower(InAttack)
	, Defense(InDefense)
	, AttackStrategy(nullptr)
	, DefenseStrategy(nullptr)
{
	
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

	ChangeHP(-finalDamage);

	//콜백을 리워드 시스템에 연결
	auto Event = make_shared<ICharacterDamagedEvent>(Name, finalDamage);
	GlobalEventManager::Get().Notify(Event);
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
