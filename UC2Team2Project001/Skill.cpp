#include "pch.h"
#include "Skill.h"
#include "Character.h"
#include "CombatComponent.h"

void ActiveSkill::UseSkill()
{
	if (!skillData.owner.get() && !skillData.target.get())
	{
		return;
	}

	for (auto effect : skillData.effects)
	{
		effect.get()->PreEffect();
	}

	
	if (!skillData.target)
		skillData.target = skillData.owner->combatManager.get()->GetTarget();

	skillData.action->ExecuteAction(skillData.owner.get(), skillData.target.get());

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
	if (!skillData.owner.get() && !skillData.target.get()) return;

	for (auto effect : skillData.effects)
	{
		effect.get()->PreEffect();
	}

	skillData.action->ExecuteAction(skillData.owner.get(), skillData.target.get());

	for (auto effect : skillData.effects)
	{
		effect.get()->PostEffect();
	}

	std::cout << "패시브 발동" << std::endl;
}
