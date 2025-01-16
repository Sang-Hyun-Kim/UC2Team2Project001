#include "pch.h"
#include "Sanctification.h"
#include "ISkillEffect.h"
#include "ISkillCondition.h"
#include "CharacterStatus.h"

Sanctification::Sanctification(Character* _owner) : ActiveSkill(_owner)
{
	skillData = FSkillData(_owner, "신성화", "3턴간 플레이어의 공격력, 방어력, 회피력을 10올리고 적의 공격력, 방어력, 회피력을 5줄인다. 쿨타임 : 5턴", 10, 5); // MP 비용 10, 쿨타임 5턴

	// 효과 1: 플레이어 능력치 강화
	skillData.effects.push_back(make_shared<IBuffEffect>(make_shared<ModifyStatState>(3, StatType::AttackPower, 10)));
	skillData.effects.push_back(make_shared<IBuffEffect>(make_shared<ModifyStatState>(3, StatType::Defense, 10)));
	skillData.effects.push_back(make_shared<IBuffEffect>(make_shared<ModifyStatState>(3, StatType::EvasionRate, 10)));

	// 효과 2: 적 능력치 약화
	skillData.effects.push_back(make_shared<IBuffEffect>(make_shared<ModifyStatState>(3, StatType::AttackPower, -5)));
	skillData.effects.push_back(make_shared<IBuffEffect>(make_shared<ModifyStatState>(3, StatType::Defense, -5)));
	skillData.effects.push_back(make_shared<IBuffEffect>(make_shared<ModifyStatState>(3, StatType::EvasionRate, -5)));

	// 조건 추가
	skillData.conditions.push_back(make_shared<ManaCondition>());     
	skillData.conditions.push_back(make_shared<CooldownCondition>()); 
	skillData.conditions.push_back(make_shared<AliveCondition>());

	SkillInit(this);
}
