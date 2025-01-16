#include "pch.h"
#include "PoisonTrigger.h"

#include "ISkillCondition.h"
#include "CharacterStatus.h"


PoisonTrigger::PoisonTrigger(Character* _owner) :ActiveSkill(_owner)
{
	skillData = FSkillData(_owner, "독 격발", "쌓은 중독 카운트를 모두 소비하여 대미지(중독 카운트 X 중독 대미지 X 남은 지속시간)를 입힌다. 쿨타임 : 4턴", 0, 4);

	skillData.action = make_shared<PoisonTriggerAction>();

	skillData.effects.push_back(std::make_shared<IRemoveStateEffect>(typeid(PoisonState)));


	skillData.conditions.push_back(make_shared<ManaCondition>());
	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<AliveCondition>());

	SkillInit(this);
}
