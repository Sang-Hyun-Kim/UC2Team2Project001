#include "pch.h"
#include "ISkillAction.h"
#include "Character.h"
#include "GlobalEventManager.h"
#include "ICharacterEventTypes.h"
#include "CombatComponent.h"
#include "Skill.h"

void AttackAction::ExecuteAction()
{
	shared_ptr<Character> self = parentSkill->GetSkillData().owner;
	shared_ptr<Character> target = parentSkill->GetTarget();

	// 치명타 확률 계산
	int CriticalChance = (int)(CharacterUtility::GetStat(self.get(), StatType::CriticalChance) * 100);
	bool IsCritical = (rand() % 100) <= CriticalChance;

	int BaseDamage = (int)CharacterUtility::GetStat(self.get(), StatType::AttackPower);
	int FianlDamage = IsCritical ? (BaseDamage * 2) : BaseDamage;

	auto Event = make_shared<ICharacterAttackEvent>(self->GetName(), FianlDamage);
	GlobalEventManager::Get().Notify(Event);

	target->combatManager->TakeDamage(FianlDamage);
}
