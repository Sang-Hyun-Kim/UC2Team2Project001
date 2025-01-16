#include "pch.h"
#include "Skill.h"
#include "ISkillCondition.h"
#include "StatComponent.h"
#include "UStatusComponent.h"

#include "Character.h"

bool ManaCondition::Check(Skill* _checkSkill)
{
	const auto& skillData = _checkSkill->GetSkillData();
	if (!skillData.owner)
	{
		return false;
	}

	int MpValue = CharacterUtility::GetStat(skillData.owner, StatType::MP);

	return MpValue >= skillData.mpCost;
}

bool CooldownCondition::Check(Skill* _checkSkill)
{
	const auto& skillData = _checkSkill->GetSkillData();
	return skillData.currentCooldown <= 0;
}

bool AliveCondition::Check(Skill* _checkSkill)
{
	return !CharacterUtility::IsDead(_checkSkill->GetTarget());
}

bool StunCondition::Check(Skill* _checkSkill)
{
	const auto& skillData = _checkSkill->GetSkillData();
	return !skillData.owner->statusManager->GetState<StunState>();
}
