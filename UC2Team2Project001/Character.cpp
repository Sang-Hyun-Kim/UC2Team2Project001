#include "pch.h"
#include "Character.h"
#include "IStrategy.h"
#include <memory>
#include "IEventTypes.h"
#include "StatComponent.h"
#include "GlobalEventManager.h"


Character::Character(): AttackStrategy(nullptr), DefenseStrategy(nullptr)
{
}

Character::Character(const string& InName) : CharacterName(InName), AttackStrategy(nullptr), DefenseStrategy(nullptr)
{
	StatManager = std::make_shared<UStatsComponent>(this);
	StatManager.get()->BeginPlay();
}

void Character::Attack(Character* Target)
{
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

	auto NewDamageEvent = std::make_shared<ICharacterDamagedEvent>(GetName(),finalDamage);
	GlobalEventManager::Get().Notify(NewDamageEvent);

	// HP 수정
	StatManager->ModifyStat(StatType::HP, -static_cast<float>(finalDamage));
}

void Character::SetAttackStrategy(std::shared_ptr<IAttackStrategy> NewAttackStrategy)
{
	AttackStrategy = std::move(NewAttackStrategy);
}

void Character::SetDefenseStrategy(std::shared_ptr<IDefenseStrategy> NewDefenseStrategy)
{
	DefenseStrategy = std::move(NewDefenseStrategy);
}
