#include "pch.h"
#include "ISkillAction.h"
#include "Character.h"
#include "GlobalEventManager.h"
#include "ICharacterEventTypes.h"
#include "CombatComponent.h"
#include "Skill.h"
#include "UStatusComponent.h"
#include "StatComponent.h"
#include "IStrategy.h"



void NormalAttackAction::ExecuteAction()
{
	Character* self = parentSkill->GetSkillData().owner;

	Character* target = parentSkill->GetTarget();

	if (CharacterUtility::IsDead(self))
	{
		std::cout << "Self 캐릭터가 죽어서 액션을 사용할 수 없습니다" << std::endl;
		return;
	}

	if (!target)
	{
		cout << "타겟이 없습니다." << endl;
		return;
	}

	if (!self->combatManager->GetAttackStrategy())
	{
		cout << "공격 전략이 설정되지 않았습니다." << endl;
		return;
	}

	float Damage = CharacterUtility::GetStat(self, StatType::AttackPower);
	
	self->combatManager->GetAttackStrategy()->Attack(self, target, Damage);
}


void AttackAction::ExecuteAction()
{
	Character* self = parentSkill->GetSkillData().owner;

	Character* target = parentSkill->GetTarget();

	if (CharacterUtility::IsDead(self))
	{
		return;
	}

	if (!target)
	{
		cout << "타겟이 없습니다." << endl;
		return;
	}

	if (!self->combatManager->GetAttackStrategy())
	{
		cout << "공격 전략이 설정되지 않았습니다." << endl;
		return;
	}

	// 공격 전략 실행
	self->combatManager->GetAttackStrategy()->Attack(self, target, attackDamage);
}

void PoisonIntensifierAction::ExecuteAction()
{
	Character* target = parentSkill->GetTarget();
	auto poisonState = target->statusManager->GetState<PoisonState>();
	if (poisonState)
	{
		poisonState->ApplyStack(poisonState->currentStack);
	}
}

void PoisonPogAction::ExecuteAction()
{
	Character* target = parentSkill->GetTarget();
	auto poisonState = target->statusManager->GetState<PoisonState>();
	if (poisonState)
	{
		poisonState->ApplyStack(2);
		poisonState->ApplyEffect(target);
	}
}

void PoisonTriggerAction::ExecuteAction()
{
	Character* target = parentSkill->GetTarget();
	auto poisonState = target->statusManager->GetState<PoisonState>();

	if (poisonState)
	{
		float TriggerPoisonDamage = poisonState->currentStack * poisonState->GetDuration();
		target->statManager->ModifyStat(StatType::HP, TriggerPoisonDamage);
		cout << "독을 격발하였습니다" << endl;
	}
}
