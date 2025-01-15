#include "pch.h"
#include "Skill.h"
#include "Character.h"
#include "CombatComponent.h"

void ActiveSkill::UseSkill()
{
	if (!skillData.owner.get())
	{
		return;
	}

	for (auto effect : skillData.effects)
	{
		effect.get()->PreEffect();
	}

	skillData.action->ExecuteAction();

	for (auto effect : skillData.effects)
	{
		effect.get()->PostEffect();
	}

	//self->SetCoolDown(); 스킬 쿨다운 적용
	//self->SetModify();

	cout << "액티브 스킬 사용 완료" << endl;
}

void PassiveSkill::UseSkill()
{
	if (!skillData.owner.get())
	{
		return;
	}

	for (auto effect : skillData.effects)
	{
		effect.get()->PreEffect();
	}

	skillData.action->ExecuteAction();

	for (auto effect : skillData.effects)
	{
		effect.get()->PostEffect();
	}

	std::cout << "패시브 발동" << std::endl;
}

shared_ptr<Character> Skill::GetTarget()
{
	return skillData.owner->combatManager->GetTarget();
}
