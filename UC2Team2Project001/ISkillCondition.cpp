#include "pch.h"
#include "Skill.h"
#include "ISkillCondition.h"
#include "StatComponent.h"

#include "Character.h"

bool ManaCondition::Check(Skill* chekckSkill)
{
    const auto& SkillData = chekckSkill->GetSkillData();
    if (!SkillData.owner)
    {
        return false;
    }

    int MpValue = CharacterUtility::GetStat(SkillData.owner, StatType::MP);

    return MpValue >= SkillData.mpCost;

}

bool CooldownCondition::Check(Skill* chekckSkill)
{
    const auto& SkillData = chekckSkill->GetSkillData();
    return SkillData.currentCooldown <= 0;
}

bool AliveCondition::Check(Skill* chekckSkill)
{
    const auto& SkillData = chekckSkill->GetSkillData();
    return !CharacterUtility::IsDead(chekckSkill->GetTarget());
}