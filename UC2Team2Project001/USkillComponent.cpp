#include "pch.h"
#include "USkillComponent.h"
#include "Skill.h"
#include <unordered_set>

unordered_map<string, shared_ptr<Skill>> USkillComponent::ChooseSkillList(SkillType _skillType)
{
    return _skillType == SkillType::ACTIVE ? activeSkillList : passiveSkillList;;
}

shared_ptr<Skill> USkillComponent::GetSkill(SkillType _skillType, string _skillName)
{
    auto skillList = ChooseSkillList(_skillType);

    for (int i = 0; i < skillList.size(); i++)
    {
        if (skillList.find(_skillName) != skillList.end())
        {
            return skillList[_skillName];
        }
    }

    return nullptr;
}

void USkillComponent::AddSkill(shared_ptr<ActiveSkill> _activeSkill)
{
    activeSkillList[_activeSkill->GetSkillData().skillName] = _activeSkill;
}

void USkillComponent::AddSkill(shared_ptr<PassiveSkill> _passiveSkill)
{
    passiveSkillList[_passiveSkill->GetSkillData().skillName] = _passiveSkill;
}

void USkillComponent::RemoveSkill(SkillType _skillType, string _skillName)
{
    auto skillList = ChooseSkillList(_skillType);
    skillList.erase(_skillName);
}

void USkillComponent::UseSkill(SkillType _skillType, string _skillName)
{
    auto skillList = ChooseSkillList(_skillType);
    skillList[_skillName]->UseSkill();
}

void USkillComponent::SetSkillCooldown(SkillType _skillType, string _skillName, int cooldown)
{

}
