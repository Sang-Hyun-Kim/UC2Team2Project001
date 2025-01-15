#include "pch.h"
#include "ISkillAction.h"
#include "Character.h"
#include "GlobalEventManager.h"
#include "ICharacterEventTypes.h"
#include "CombatComponent.h"

void AttackAction::ExecuteAction(Character* _self, Character* _target)
{
	// 치명타 확률 계산
	int CriticalChance = (int)(CharacterUtility::GetStat(_self, StatType::CriticalChance) * 100);
	bool IsCritical = (rand() % 100) <= CriticalChance;

	int BaseDamage = (int)CharacterUtility::GetStat(_self, StatType::AttackPower);
	int FianlDamage = IsCritical ? (BaseDamage * 2) : BaseDamage;

	auto Event = make_shared<ICharacterAttackEvent>(_self->GetName(), FianlDamage);
	GlobalEventManager::Get().Notify(Event);

	_target->combatManager->TakeDamage(FianlDamage);
}
