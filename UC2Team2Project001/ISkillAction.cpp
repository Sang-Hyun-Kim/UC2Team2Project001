#include "pch.h"
#include "ISkillAction.h"
#include "Character.h"
#include "GlobalEventManager.h"
#include "ICharacterEventTypes.h"
#include "CombatComponent.h"
#include "Skill.h"
#include "UStatusComponent.h"
#include "StatComponent.h"

void AttackAction::ExecuteAction()
{
	Character* self = parentSkill->GetSkillData().owner;

	Character* target = parentSkill->GetTarget();

	auto Event = make_shared<ICharacterAttackEvent>(self->GetName(), attackDamage);
	GlobalEventManager::Get().Notify(Event);

	target->combatManager->TakeDamage((int)attackDamage);
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
