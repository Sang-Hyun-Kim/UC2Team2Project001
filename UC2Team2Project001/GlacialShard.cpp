#include "pch.h"
#include "GlacialShard.h"
#include "ISkillCondition.h"

// 빙하의 파편 스킬 생성자 구현
GlacialShard::GlacialShard(Character* _owner) : ActiveSkill(_owner)
{
	skillData = FSkillData(
		_owner,
		"빙하의 파편",
		"적 1명에게 공격력의 200% 피해를 입히고, 방어력을 2턴 동안 20% 감소시킵니다.",
		20,   // 마나 감소량
		5     // 쿨타임
	);

	// 액션 설정
	skillData.action = std::make_shared<GlacialShardAction>(2.0f, 0.2f, 2);

	// 조건 설정
	skillData.conditions.push_back(std::make_shared<ManaCondition>());
	skillData.conditions.push_back(std::make_shared<CooldownCondition>());
	skillData.conditions.push_back(std::make_shared<AliveCondition>());
	skillData.conditions.push_back(std::make_shared<StunCondition>());

	// 스킬 초기화
	SkillInit(this);
}