#include "pch.h"
#include "PoisonInfusion.h"
#include "ISkillCondition.h"



PoisonInfusion::PoisonInfusion(Character* _owner) :ActiveSkill(_owner)
{
	skillData = FSkillData(_owner, "맹독 부여", 0, 2);

	skillData.action = make_shared<PoisonIntensifierAction>();

	shared_ptr<ISkillEffect> lifeEffect = make_shared<IPoisonEffect>();
	skillData.effects.push_back(lifeEffect);

	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<AliveCondition>());

	SkillInit(this);
}
