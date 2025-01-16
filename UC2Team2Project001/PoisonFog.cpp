#include "pch.h"
#include "PoisonFog.h"
#include "ISkillAction.h"
#include "ISkillCondition.h"



PoisonFog::PoisonFog(Character* _owner) :ActiveSkill(_owner)
{
	skillData = FSkillData(_owner, "독 안개", "중독 카운트를 2개 쌓고 대상의 중독 카운트만큼 대미지를 입힌다. 쿨타임 : 2턴", 0, 2);

	skillData.action = make_shared<PoisonPogAction>();

	shared_ptr<ISkillEffect> poisonEffect = make_shared<IPoisonEffect>(2);
	skillData.effects.push_back(poisonEffect);

	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<AliveCondition>());
	skillData.conditions.push_back(make_shared<StunCondition>());

	SkillInit(this);
}
