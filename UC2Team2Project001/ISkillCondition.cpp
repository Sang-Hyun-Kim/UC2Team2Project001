#include "pch.h"
#include "Skill.h"
#include "ISkillCondition.h"
#include "StatComponent.h"
#include "UStatusComponent.h"
#include "ConsoleLayout.h"
#include "Character.h"

bool ManaCondition::Check(Skill* _checkSkill)
{
	const auto& skillData = _checkSkill->GetSkillData();
	_owner = skillData.owner;
	if (!skillData.owner)
	{
		return false;
	}

	int MpValue = CharacterUtility::GetStat(skillData.owner, StatType::MP);

	return MpValue >= skillData.mpCost;
}

void ManaCondition::CannotUseSkill()
{
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "마나가 부족합니다.", true, ConsoleColor::Magenta);
}

bool CooldownCondition::Check(Skill* _checkSkill)
{
	const auto& skillData = _checkSkill->GetSkillData();
	_owner = skillData.owner;
	return skillData.currentCooldown <= 0;
}

void CooldownCondition::CannotUseSkill()
{
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "스킬이 쿨다운 중입니다.", true, ConsoleColor::Magenta);
}

bool AliveCondition::Check(Skill* _checkSkill)
{
	return !CharacterUtility::IsDead(_checkSkill->GetSkillData().owner) && !CharacterUtility::IsDead(_checkSkill->GetTarget());
}

void AliveCondition::CannotUseSkill()
{
}

bool StunCondition::Check(Skill* _checkSkill)
{
	const auto& skillData = _checkSkill->GetSkillData();
	_owner = skillData.owner;
	return !skillData.owner->statusManager->GetState<StunState>();
}

void StunCondition::CannotUseSkill()
{
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, _owner->GetName() + "은(는) 기절 상태 입니다.", true, ConsoleColor::Magenta);
}
