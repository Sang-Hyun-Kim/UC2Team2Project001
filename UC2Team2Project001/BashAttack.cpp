#include "pch.h"
#include "BashAttack.h"
#include "ISkillCondition.h"


BashAttack::BashAttack(Character* _owner) : ActiveSkill(_owner)
{
	skillData = FSkillData(_owner, "강타", "100%의 대미지를 준 이후 방어력 만큼의 추가 대미지를 준다.", 5, 0);

	skillData.action = std::make_shared<NormalAttackAction>();

	shared_ptr<ISkillEffect> defenseBasedDamageEffect = make_shared<IDefenseBasedDamageEffect>();
	skillData.effects.push_back(defenseBasedDamageEffect);

	skillData.conditions.push_back(make_shared<AliveCondition>());
	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<ManaCondition>());
	skillData.conditions.push_back(make_shared<StunCondition>());

	SkillInit(this);
}
