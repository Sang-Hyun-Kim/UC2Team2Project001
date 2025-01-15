#include "pch.h"
#include "ISkillEffect.h"
#include "Character.h"
#include "Skill.h"
#include "CharacterStatus.h"
#include "UStatusComponent.h"

void ILifeStealEffect::PostEffect()
{
	CharacterUtility::ModifyStat(parentSkill->GetTarget(), StatType::HP, lifeAmount);

	cout << "흡혈 효과 발동" << endl;
}

void IBuffEffect::PostEffect()
{
	CharacterUtility::ModifyStat(parentSkill->GetTarget(), type, modifyValue);

	// 효과 발동 내역 출력
}

IPoisonEffect::IPoisonEffect(int amountStack)
{
	states.push_back(make_shared<PoisonState>(2, 5, amountStack));
}

void IPoisonEffect::PostEffect()
{
	const auto& skillData = parentSkill->GetSkillData();
	Character* target = parentSkill->GetTarget();

	for (auto state : states)
	{
		target->StatusComponent->AddState(state);
	}
}


void IRemoveStateEffect::PostEffect()
{
	Character* target = parentSkill->GetTarget();

	if (!target || !target->StatusComponent)
	{
		std::cout << "대상이 없거나 상태 컴포넌트가 없습니다.\n";
		return;
	}

	auto& statusComponent = target->StatusComponent;

	bool isSuccess = statusComponent->RemoveState(stateType);

	if (isSuccess)
		cout << "성공했습니다 상태제거에" << endl;
	else
		cout << "실패했습니다 상태제거에" << endl;
}