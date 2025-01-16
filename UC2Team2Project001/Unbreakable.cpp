#include "pch.h"
#include "Unbreakable.h"
#include "ISkillCondition.h"
#include "ICharacterEventTypes.h"

Unbreakable::Unbreakable(Character* _owner) : PassiveSkill(_owner)
{
	skillData = FSkillData(_owner, "불굴의 의지", "죽음에 이르는 공격을 받았을 때 HP를 1로 고정하고 4턴 이내 적을 처치하지 못할 시 사망하며 적을 처치 시 HP 20을 회복한다.", 0, 0);

	//패시브 태그 설정
	handlers.insert(typeid(ICharacterStatZeroEvent));

	shared_ptr<ISkillEffect> unbreakableEffect = make_shared<IUnbreakableEffect>();
	skillData.effects.push_back(unbreakableEffect);

	skillData.conditions.push_back(make_shared<AliveCondition>());

	SkillInit(this);
}
