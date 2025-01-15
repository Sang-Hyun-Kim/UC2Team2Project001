#include "pch.h"
#include "ISkillEffect.h"
#include "Character.h"
#include "Skill.h"

void ILifeStealEffect::PostEffect()
{
	CharacterUtility::ModifyStat(skill.get()->GetTarget().get(), StatType::HP, lifeAmount);

	cout << "흡혈 효과 발동" << endl;
}

void IBuffEffect::PostEffect()
{
	CharacterUtility::ModifyStat(skill.get()->GetTarget().get(), type, modifyValue);

	// 효과 발동 내역 출력
}
