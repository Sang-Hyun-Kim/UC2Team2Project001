#include "pch.h"
#include "BashAttack.h"
#include "ISkillCondition.h"


BashAttack::BashAttack(Character* _owner) : ActiveSkill(_owner)
{
	skillData = FSkillData(_owner, "강타", 5, 0);

	skillData.action = make_shared<AttackAction>(10);

	shared_ptr<ISkillEffect> defenseBasedDamageEffect = make_shared<IDefenseBasedDamageEffect>();
	skillData.effects.push_back(defenseBasedDamageEffect);

	skillData.conditions.push_back(make_shared<AliveCondition>());
	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<ManaCondition>());

	SkillInit(this);
}
