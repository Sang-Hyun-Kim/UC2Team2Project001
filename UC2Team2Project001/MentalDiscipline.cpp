#include "pch.h"
#include "MentalDiscipline.h"
#include "ISkillCondition.h"
#include "UStatusComponent.h"

MentalDiscipline::MentalDiscipline(Character* _owner)
{
	skillData = FSkillData(_owner, "정신 수양", 10, 2);

	skillData.action = nullptr;

	shared_ptr<ISkillEffect> mentalDisciplineEffect = make_shared<IBuffEffect>(make_shared<ModifyDefenseState>(4, 10));
	skillData.effects.push_back(mentalDisciplineEffect);

	skillData.conditions.push_back(make_shared<AliveCondition>());
	skillData.conditions.push_back(make_shared<CooldownCondition>());
	skillData.conditions.push_back(make_shared<ManaCondition>());

	SkillInit(this);
}
