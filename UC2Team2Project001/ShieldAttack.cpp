#include "pch.h"
#include "ShieldAttack.h"
#include "ISkillCondition.h"
#include "UStatusComponent.h"

ShieldAttack::ShieldAttack(Character* _owner)
{
	skillData = FSkillData(_owner, "방패 후려치기", "방어력 + 15 만큼의 대미지를 입힌 후 2턴간 기절이 발생한다. 쿨타임 : 3턴", 10, 3);

	float damage = CharacterUtility::GetStat(_owner, StatType::Defense) + 15;
	skillData.action = make_shared<AttackAction>(damage);

	shared_ptr<ISkillEffect> stunEffect = make_shared<IStunEffect>(2);
	skillData.effects.push_back(stunEffect);

	skillData.conditions.push_back(make_shared<AliveCondition>());
	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<ManaCondition>());
	skillData.conditions.push_back(make_shared<StunCondition>());

	SkillInit(this);
}
