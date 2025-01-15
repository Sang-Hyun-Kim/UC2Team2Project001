#include "pch.h"
#include "LifeStealAttack.h"
#include "ISkillCondition.h"

LifeStealAttack::LifeStealAttack(Character* _owner) : ActiveSkill(_owner)
{
	skillData = FSkillData(_owner,"흡혈 공격", 10, 3);

	skillData.action = make_shared<AttackAction>(CharacterUtility::GetStat(_owner, StatType::AttackPower));

	shared_ptr<ISkillEffect> lifeEffect = make_shared<ILifeStealEffect>(10);
	skillData.effects.push_back(lifeEffect);

	skillData.conditions.push_back(make_shared<AliveCondition>());
	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<ManaCondition>());

	SkillInit<Skill>();
}
