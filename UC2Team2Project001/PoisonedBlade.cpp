#include "pch.h"
#include "PoisonedBlade.h"
#include "ISkillCondition.h"


PoisonedBlade::PoisonedBlade(Character* _owner) :ActiveSkill(_owner)
{
	skillData = FSkillData(_owner, "독이 묻은 칼", "적에게 10의 대미지를 입힌 후 중독 카운트를 하나 올린다.", 0, 0);
	skillData.action = make_shared<AttackAction>(10);

	shared_ptr<ISkillEffect> lifeEffect = make_shared<IPoisonEffect>(1);
	skillData.effects.push_back(lifeEffect);

	skillData.conditions.push_back(make_shared<ManaCondition>());
	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<AliveCondition>());
	skillData.conditions.push_back(make_shared<StunCondition>());

	SkillInit(this);
}
