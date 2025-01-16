#include "pch.h"
#include "CursedSeal.h"
#include "ISystemTypes.h"
#include "CharacterStatus.h"


CursedSeal::CursedSeal(Character* _owner) : PassiveSkill(_owner)
{
	// 스킬 기본 정보 설정
	skillData = FSkillData(_owner, "저주의 인장", 0, 0);

	// 상태 추가: 5턴 동안, 2턴마다 3 데미지 적용
	skillData.effects.push_back(make_shared<IBuffEffect>(make_shared<CursedSealState>(INFINITEDURATION, 3, 2)));

	SkillInit(this);
}