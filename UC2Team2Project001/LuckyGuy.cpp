#include "pch.h"
#include "LuckyGuy.h"

#include "ISkillCondition.h"
#include "StatComponent.h"
#include "ICombatEventTypes.h"

LuckyGuy::LuckyGuy(Character* _owner) : PassiveSkill(_owner)
{
	skillData = FSkillData(_owner, "행운의 사나이", 0, 0);

	handlers.insert(typeid(IPlayerStageClearEvent));

	skillData.effects.push_back(make_shared<LuckyRewardEffect>(100));

	skillData.conditions.push_back(make_shared<AliveCondition>());

	SkillInit(this);
}

