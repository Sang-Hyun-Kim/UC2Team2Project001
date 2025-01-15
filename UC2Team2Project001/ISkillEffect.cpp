#include "pch.h"
#include "ISkillEffect.h"
#include "Character.h"
#include "Skill.h"
#include "CombatComponent.h"
#include "UStatusComponent.h"
#include "Monster.h"
#include "CharacterStatus.h"
#include "UStatusComponent.h"

void ILifeStealEffect::PostEffect()
{
	CharacterUtility::ModifyStat(parentSkill->GetTarget(), StatType::HP, lifeAmount);

	cout << "흡혈 효과 발동" << endl;
}

IBuffEffect::IBuffEffect(shared_ptr<ICharacterState> _state)
	: state(_state)
{
}

void IBuffEffect::PostEffect()
{
	parentSkill->GetTarget()->StatusComponent->AddState(state);
}

void IDefenseBasedDamageEffect::PostEffect()
{
	Character* self = parentSkill->GetSkillData().owner;
	Character* target = parentSkill->GetTarget();

	float armour = CharacterUtility::GetStat(self, StatType::Defense);

	cout << "방어력 " << armour << "만큼 추가 대미지가 발생 했습니다." << endl;

	target->combatManager->TakeDamage(armour);
}

void IOnePointAttackEffect::PostEffect()
{
	Monster* target = dynamic_cast<Monster*>(parentSkill->GetTarget());

	if (!target->IsBoss())
	{
		float defense = CharacterUtility::GetStat(target, StatType::Defense);
		parentSkill->GetTarget()->StatusComponent->AddState(make_shared<ModifyDefenseState>(3, -defense));
		parentSkill->GetTarget()->StatusComponent->AddState(make_shared<StunState>(1));
	}
}

IStunEffect::IStunEffect(int _duration)
{
	stunState = make_shared<StunState>(_duration);
}

void IStunEffect::PostEffect()
{
	parentSkill->GetTarget()->StatusComponent->AddState(stunState);
	cout << "기절 상태 적용" << endl;
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