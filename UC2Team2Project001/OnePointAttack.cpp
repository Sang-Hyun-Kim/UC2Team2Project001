#include "pch.h"
#include "OnePointAttack.h"
#include "ISkillCondition.h"

OnePointAttack::OnePointAttack(Character* _owner) : ActiveSkill(_owner)
{
	skillData = FSkillData(_owner, "일점 돌파", "40의 대미지를 준 후 보스가 아닐 경우 3턴간 상대방의 방어력을 0으로 만들고 1턴간 기절한다. 쿨타임 : 5턴", 10, 5);

	skillData.action = make_shared<AttackAction>(40);

	shared_ptr<ISkillEffect> mentalDisciplineEffect = make_shared<IOnePointAttackEffect>();
	skillData.effects.push_back(mentalDisciplineEffect);

	skillData.conditions.push_back(make_shared<AliveCondition>());
	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<ManaCondition>());

	SkillInit(this);
}
