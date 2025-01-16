#include "pch.h"
#include "RageGatheringSkill.h"
#include "ISkillCondition.h"
#include "CharacterStatus.h"

// 액티브 스킬 정의
RageGatheringSkill::RageGatheringSkill(Character* _owner) : ActiveSkill(_owner)
{
	skillData = FSkillData(
		_owner,
		"분노 모으기",
		"이번 턴 아무 것도 하지 않지만, 다음 턴 기본 공격에 공격력의 500% 피해를 입힙니다. 이후 기본 상태로 복구됩니다.",
		20,   // 마나 감소
		3     // 쿨타임
	);

	// 스킬 조건 설정
	skillData.conditions.push_back(std::make_shared<ManaCondition>());
	skillData.conditions.push_back(std::make_shared<CooldownCondition>());
	skillData.conditions.push_back(std::make_shared<AliveCondition>());
	skillData.conditions.push_back(std::make_shared<StunCondition>());

	// 스킬 효과: 분노 상태 부여
	skillData.effects.push_back(
		std::make_shared<IBuffEffect>(std::make_shared<RageState>(1, 5.0f), true // 1턴 지속, 500% 피해
		)
	);

	// 스킬 초기화
	SkillInit(this);
}