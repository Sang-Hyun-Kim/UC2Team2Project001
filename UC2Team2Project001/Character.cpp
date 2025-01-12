#include "pch.h"
#include "Character.h"
#include "IStrategy.h"
#include "IEventTypes.h"
#include "GlobalEventManager.h"
#include "StatComponent.h"
#include <memory>


Character::Character(): AttackStrategy(nullptr), DefenseStrategy(nullptr)
{
	StatManager = std::make_shared<UStatsComponent>(this);
}

Character::Character(const string& InName) : CharacterName(InName), AttackStrategy(nullptr), DefenseStrategy(nullptr)
{
	StatManager = std::make_shared<UStatsComponent>(this);
	StatManager.get()->BeginPlay();
}

void Character::Attack(Character* Target)
{
	if (StatManager->IsDead())
	{
		return;
	}

	if (!Target)
	{
		std::cout << "타겟이 없습니다." << std::endl;
		return;
	}

	if (!AttackStrategy)
	{
		std::cout << "공격 전략이 설정되지 않았습니다." << std::endl;
		return;
	}

	// 공격 전략 실행
	AttackStrategy->Attack(this, Target);
}

void Character::TakeDamage(int IncomingDamage)
{
	int finalDamage = IncomingDamage;

	// 방어 전략 적용
	if (DefenseStrategy)
	{
		finalDamage = DefenseStrategy->CalculateDamageReceived(this, IncomingDamage);
	}

	//콜백을 리워드 시스템에 연결
	auto Event = make_shared<ICharacterDamagedEvent>(CharacterName, finalDamage, StatManager->GetStat(StatType::HP));
	GlobalEventManager::Get().Notify(Event);

	StatManager->ModifyStat(StatType::HP, (float) - finalDamage);
}

void Character::SetAttackStrategy(shared_ptr<IAttackStrategy> NewAttackStrategy)
{
	AttackStrategy = move(NewAttackStrategy);
}

void Character::SetDefenseStrategy(shared_ptr<IDefenseStrategy> NewDefenseStrategy)
{
	DefenseStrategy = move(NewDefenseStrategy);
}
