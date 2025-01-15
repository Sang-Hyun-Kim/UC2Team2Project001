#include "pch.h"
#include "Plague.h"
#include "ISkillCondition.h"
#include "ICombatEventTypes.h"


Plague::Plague(Character* _owner) :PassiveSkill(_owner)
{
	skillData = FSkillData(_owner, "역병", 0, 0);

	//패시브 태그 설정
	handlers.insert(typeid(IPlayerBattleAttackEvent));
	

	shared_ptr<ISkillEffect> lifeEffect = make_shared<IPoisonEffect>(1);
	skillData.effects.push_back(lifeEffect);

	skillData.conditions.push_back(make_shared<AliveCondition>());

	SkillInit(this);
}
