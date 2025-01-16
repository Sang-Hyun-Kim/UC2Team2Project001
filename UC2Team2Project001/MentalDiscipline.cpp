#include "pch.h"
#include "MentalDiscipline.h"
#include "ISkillCondition.h"
#include "UStatusComponent.h"

MentalDiscipline::MentalDiscipline(Character* _owner) : ActiveSkill(_owner)
{
	skillData = FSkillData(_owner, "정신 수양", "4턴간 10의 방어력을 올려준다. 쿨타임 : 2턴", 10, 2);

	skillData.action = nullptr;

	shared_ptr<ISkillEffect> mentalDisciplineEffect = make_shared<IBuffEffect>(make_shared<ModifyDefenseState>(4, 10), true);
	skillData.effects.push_back(mentalDisciplineEffect);

	skillData.conditions.push_back(make_shared<AliveCondition>());
	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<ManaCondition>());
	skillData.conditions.push_back(make_shared<StunCondition>());

	SkillInit(this);
}
