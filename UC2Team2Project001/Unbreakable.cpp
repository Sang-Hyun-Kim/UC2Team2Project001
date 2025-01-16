#include "pch.h"
#include "Unbreakable.h"
#include "ISkillCondition.h"
#include "ICharacterEventTypes.h"

Unbreakable::Unbreakable(Character* _owner) : PassiveSkill(_owner)
{
	skillData = FSkillData(_owner, "불굴의 의지", 0, 0);

	//패시브 태그 설정
	handlers.insert(typeid(ICharacterStatZeroEvent));

	shared_ptr<ISkillEffect> unbreakableEffect = make_shared<IUnbreakableEffect>();
	skillData.effects.push_back(unbreakableEffect);

	skillData.conditions.push_back(make_shared<AliveCondition>());

	SkillInit(this);
}
