#include "pch.h"
#include "Patience.h"
#include "ISkillCondition.h"
#include "ISystemTypes.h"

Patience::Patience(Character* _owner) : PassiveSkill(_owner)
{
	skillData = FSkillData(_owner, "인내심", 0, 0);

	//패시브 태그 설정
	handlers.insert(typeid(ITurnStart));

	shared_ptr<IHealingEffect> healingEffect = make_shared<IHealingEffect>(10);
	skillData.effects.push_back(healingEffect);

	skillData.conditions.push_back(make_shared<AliveCondition>());

	SkillInit(this);
}
