#include "pch.h"
#include <memory>
#include "Character.h"
#include "IStrategy.h"
#include "IEventTypes.h"
#include "GlobalEventManager.h"
#include "StatComponent.h"

Character::Character()
	: AttackStrategy(nullptr), DefenseStrategy(nullptr)
{
	
}

Character::Character(const string& InName)
	: CharacterName(InName), AttackStrategy(nullptr), DefenseStrategy(nullptr)
{
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

	StatManager->ModifyStat(StatType::HP, -finalDamage);

	//콜백을 리워드 시스템에 연결
	auto Event = make_shared<ICharacterDamagedEvent>(CharacterName, finalDamage);
	GlobalEventManager::Get().Notify(Event);
}

void Character::SetAttackStrategy(shared_ptr<IAttackStrategy> NewAttackStrategy)
{
	AttackStrategy = move(NewAttackStrategy);
}

void Character::SetDefenseStrategy(shared_ptr<IDefenseStrategy> NewDefenseStrategy)
{
	DefenseStrategy = move(NewDefenseStrategy);
}
