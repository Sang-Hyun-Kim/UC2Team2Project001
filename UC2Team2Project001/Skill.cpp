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

void Skill::SkillInit(Skill* _ownerSkill)
{
	if (skillData.action)
	{
		skillData.action.get()->SetSkill(_ownerSkill);
	}
	for (auto effect : skillData.effects)
	{
		if (effect)
		{
			effect.get()->SetSkill(_ownerSkill);
		}
	}
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

void PassiveSkill::PassiveSkillRegisterTrigger()
{

	//handlers.insert(typeid(ICharacterDamagedEvent));
	//handlers.insert(typeid(ICharacterDeadEvent));

	std::cout << "[PassiveSkill] RegisterTrigger() - " << "이벤트를 처리하도록 등록했습니다.\n";

}

void PassiveSkill::PassiveSkillUnRegisterTrigger()
{

	//handlers.erase(typeid(ICharacterDamagedEvent));
	//handlers.erase(typeid(ICharacterDeadEvent));

	std::cout << "[PassiveSkill] UnRegisterTrigger() - " << "이벤트 처리를 해제했습니다.\n";
}

void PassiveSkill::HandlePassiveEvent(std::shared_ptr<IEvent> ev)
{
	std::cout << "[PassiveSkill] HandlePassiveEvent() - 스킬 발동!\n";
	UseSkill();
}
