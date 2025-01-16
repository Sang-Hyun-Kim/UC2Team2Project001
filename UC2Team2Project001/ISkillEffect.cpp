#include "pch.h"
#include "ISkillEffect.h"
#include "Character.h"
#include "Skill.h"
#include "CombatComponent.h"
#include "UStatusComponent.h"
#include "Monster.h"
#include "CharacterStatus.h"
#include "StatComponent.h"
#include "PlayerCharacter.h"
#include "Inventory.h"

void ILifeStealEffect::PostEffect()
{
	CharacterUtility::ModifyStat(parentSkill->GetTarget(), StatType::HP, lifeAmount);

	cout << "흡혈 효과 발동" << endl;
}

IBuffEffect::IBuffEffect(shared_ptr<ICharacterState> _state, bool _isSelf)
	: state(_state), isSelf(_isSelf)
{
}

void IBuffEffect::PostEffect()
{
	Character* target;
	if (isSelf)
	{
		target = parentSkill->GetSkillData().owner;
	}
	else
	{
		target = parentSkill->GetTarget();
	}

	target->statusManager->AddState(state);
	state->ApplyEffect(target);
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
		parentSkill->GetTarget()->statusManager->AddState(make_shared<ModifyDefenseState>(3, -defense));
		parentSkill->GetTarget()->statusManager->AddState(make_shared<StunState>(1));
	}
}

IStunEffect::IStunEffect(int _duration)
{
	duration = _duration;
}

void IStunEffect::PostEffect()
{
	Character* target = parentSkill->GetTarget();

	target->statusManager->AddState(make_shared<StunState>(duration));
	cout << "기절 상태 적용! " << target->GetName() << "이(가) 기절 했습니다." << endl;
}

IPoisonEffect::IPoisonEffect(int _amountStack)
{
	amountStack = _amountStack;
}

void IPoisonEffect::PostEffect()
{
	const auto& skillData = parentSkill->GetSkillData();
	Character* target = parentSkill->GetTarget();

	target->statusManager->AddState(make_shared<PoisonState>(2, 5, amountStack));
}

void IRemoveStateEffect::PostEffect()
{
	Character* target = parentSkill->GetTarget();

	if (!target || !target->statusManager)
	{
		std::cout << "대상이 없거나 상태 컴포넌트가 없습니다.\n";
		return;
	}

	auto& statusComponent = target->statusManager;

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
}

void IUnbreakableEffect::PostEffect()
{
	Character* target = parentSkill->GetSkillData().owner;

	target->statusManager->AddState(make_shared<UnbreakableState>(4));
}

void LuckyRewardEffect::PostEffect()
{
	if (parentSkill && parentSkill->GetSkillData().owner)
	{
		Character* owner = parentSkill->GetSkillData().owner;
		if (owner->statManager)
		{
			Player* playerCharacter = dynamic_cast<Player*>(owner);
			if (playerCharacter)
			{
				playerCharacter->inventoryComponent->addGold(goldAmount);

				// 캐릭터의 골드 스탯 증가			
				std::cout << owner->GetName() << "은(는) 스테이지 클리어로 " << goldAmount << "골드를 획득했습니다.\n";
			}			
		}
	}
}
