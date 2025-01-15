#include "pch.h"
#include "PoisonTrigger.h"

#include "ISkillCondition.h"
#include "CharacterStatus.h"


PoisonTrigger::PoisonTrigger(Character* _owner) :ActiveSkill(_owner)
{
	skillData = FSkillData(_owner, "독 격발", 0, 4);

	skillData.action = make_shared<PoisonTriggerAction>();

	skillData.effects.push_back(std::make_shared<IRemoveStateEffect>(typeid(PoisonState)));


	skillData.conditions.push_back(make_shared<ManaCondition>());
	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<AliveCondition>());

	SkillInit(this);
}
