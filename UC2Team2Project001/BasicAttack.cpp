#include "pch.h"
#include "BasicAttack.h"
#include "ISkillCondition.h"

BasicAttack::BasicAttack(Character* _owner)
{
	skillData = FSkillData(_owner, "기본 공격", "캐릭터 공격력 만큼 적에게 대미지를 준다.", 0, 0);

	skillData.action = make_shared<AttackAction>(CharacterUtility::GetStat(_owner, StatType::AttackPower));

	skillData.conditions.push_back(make_shared<AliveCondition>());

	SkillInit(this);
}
