#include "pch.h"
#include "Skill.h"
#include "Character.h"
#include "CombatComponent.h"
#include "ISkillCondition.h"


bool Skill::CanUseSkill()
{
    for (const auto& condition : skillData.conditions)
    {
        if (!condition->Check(this))
        {
            return false;
        }
    }
    return true;
}

bool Skill::UseSkill()
{
    if (!CanUseSkill())
    {
        cout << "스킬을 사용할 수 없습니다: " << skillData.skillName << endl;
        return false;
    }

    for (auto& effect : skillData.effects)
    {
        effect->PreEffect();
    }
    if (skillData.action)
    {
        skillData.action->ExecuteAction();
    }
    for (auto& effect : skillData.effects)
    {
        effect->PostEffect();
    }

    skillData.currentCooldown = skillData.maxCooldown;
    return true;
}

Character* Skill::GetTarget()
{
    return skillData.owner->combatManager->GetTarget();
}