#include "pch.h"
#include "PoisonFog.h"
#include "ISkillAction.h"
#include "ISkillCondition.h"



PoisonFog::PoisonFog(Character* _owner) :ActiveSkill(_owner)
{
	skillData = FSkillData(_owner, "독 안개", 0, 2);

	skillData.action = make_shared<PoisonPogAction>();

	//shared_ptr<ISkillEffect> lifeEffect = make_shared<IPoisonEffect>();
	//skillData.effects.push_back(lifeEffect);

	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<AliveCondition>());

	SkillInit(this);
}
