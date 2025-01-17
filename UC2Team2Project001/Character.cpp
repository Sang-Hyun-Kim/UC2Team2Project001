#include "pch.h"
#include "Character.h"
#include <memory>

#include "IStrategy.h"
#include "IEventTypes.h"
#include "GlobalEventManager.h"
#include "StatComponent.h"
#include "UStatusComponent.h"

#include "StatsLoader.h"
#include "StrategyFactory.h"
#include "CombatComponent.h"
#include "USkillComponent.h"
#include "ICharacterEventTypes.h"
#include "BasicAttack.h"
#include "SkillManager.h"
#include "Sanctification.h"
#include "PoisonedBlade.h"
#include "PoisonFog.h"
#include "MentalDiscipline.h"

Character::Character()
{
}

Character::Character(const string& _name) : displayName(_name)
{
}

void Character::ManagerRegister()
{
	statManager = std::make_shared<UStatsComponent>(this);
	combatManager = make_shared<UCombatComponent>(this);
	statusManager = make_shared<UStatusComponent>(this);
	skillManager = make_shared<USkillComponent>(this);
}

void Character::PrintCharacterInfo(int type)
{
	statManager->PrintStatus(type);
}

void Character::Initialize()
{
	ManagerRegister();

	StatsData LoadStatsData = StatsLoader::LoadFromJSON(characterName);

	statManager->Initialize(LoadStatsData);
	combatManager->Initialize(LoadStatsData);

	GlobalEventManager::Get().Subscribe(skillManager);

	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(BasicAttack), this);
}

void Character::UseItem(const string& ItemName)
{
	// TODO: 아이템 사용 로직 구현
}


