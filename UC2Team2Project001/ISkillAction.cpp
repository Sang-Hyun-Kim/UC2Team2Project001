#include "pch.h"
#include "ISkillAction.h"
#include "Character.h"
#include "GlobalEventManager.h"
#include "ICharacterEventTypes.h"
#include "CombatComponent.h"
#include "Skill.h"

void AttackAction::ExecuteAction()
{
    Character* self = parentSkill->GetSkillData().owner;

    Character* target = parentSkill->GetTarget();

    auto Event = make_shared<ICharacterAttackEvent>(self->GetName(), attackDamage);
    GlobalEventManager::Get().Notify(Event);

    target->combatManager->TakeDamage(attackDamage);
}