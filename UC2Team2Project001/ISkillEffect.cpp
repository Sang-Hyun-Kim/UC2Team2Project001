#include "pch.h"
#include "ISkillEffect.h"
#include "Character.h"
#include "Skill.h"
#include "CombatComponent.h"
#include "UStatusComponent.h"
#include "Monster.h"
#include "CharacterStatus.h"

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

	float defense = CharacterUtility::GetStat(self, StatType::Defense);

	cout << "방어력 " << defense << "만큼 추가 대미지가 발생 했습니다." << endl;

	target->combatManager->TakeDamage(defense);
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
	states.push_back(make_shared<StunState>(_duration));
}

void IStunEffect::PostEffect()
{
	Character* target = parentSkill->GetTarget();

	for (auto state : states)
	{
		target->StatusComponent->AddState(state);
	}
	cout << "기절 상태 적용! " << target->GetName() << "이(가) 기절 했습니다." << endl;
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

IHealingEffect::IHealingEffect(float _healAmount) : healAmount(_healAmount)
{
}

void IHealingEffect::PreEffect()
{
	CharacterUtility::ModifyStat(parentSkill->GetTarget(), StatType::HP, healAmount);
	cout << "인내심 발동! " << parentSkill->GetTarget()->GetName() << "이(가) 체력을 " << healAmount << "만큼 회복 했습니다." << endl;
}

IUnbreakableEffect::IUnbreakableEffect()
{
	states.push_back(make_shared<UnbreakableState>(4));
}

void IUnbreakableEffect::PostEffect()
{
	Character* target = parentSkill->GetSkillData().owner;

	for (auto state : states)
	{
		target->StatusComponent->AddState(state);
	}
}
