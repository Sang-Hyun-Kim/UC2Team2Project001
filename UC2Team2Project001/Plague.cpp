#include "pch.h"
#include "Plague.h"
#include "ISkillCondition.h"
#include "ICombatEventTypes.h"


Plague::Plague(Character* _owner) :PassiveSkill(_owner)
{
	skillData = FSkillData(_owner, "역병", "매 자신의 턴이 끝날 시 랜덤한 적에게 중독 카운트 1개를 올린다.", 0, 0);

	handlers.insert(typeid(IPlayerBattleAttackEvent));
	
	shared_ptr<ISkillEffect> lifeEffect = make_shared<IPoisonEffect>(1);
	skillData.effects.push_back(lifeEffect);

	skillData.conditions.push_back(make_shared<AliveCondition>());

	SkillInit(this);
}
