#include "pch.h"
#include "SystemContext.h"
#include "LobbySystem.h"
#include "BattleSystem.h"
#include "ShopSystem.h"
#include "PlayerCharacter.h"
#include "ICombatEventTypes.h"
#include "ICharacterEventTypes.h"
#include "ISystemTypes.h"
#include "USkillComponent.h"
#include "SkillManager.h"
#include "Skill.h"
#include "BasicAttack.h"

shared_ptr<SystemContext> GSystemContext = make_shared<SystemContext>();

SystemContext::SystemContext()
{
	lobbySystem = make_shared<LobbySystem>();
	battleSystem = make_shared<BattleSystem>();
	shopSystem = make_shared<ShopSystem>();
	currentSystem = lobbySystem;
	currentSystem->EnterSystem();

	GlobalEventManager::Get().Subscribe(battleSystem);
}

SystemContext::~SystemContext()
{
}

void SystemContext::Update()
{
	currentSystem->Update();
}

void SystemContext::MoveSystem(SystemType to, SystemType from)
{
	// System from 에서 System to 로 이동

	if (to != from)
	{
		switch (to)
		{
		case SystemType::LOBBY:
			currentSystem = lobbySystem;
			break;
		case SystemType::BATTLE:
			currentSystem = battleSystem;
			break;
		case SystemType::SHOP:
			currentSystem = shopSystem;
			break;
		default:
			break;
		}

		currentSystem->EnterSystem();
	}
}

void SystemContext::CreateCharacter(string name)
{
	player = make_shared<Player>("Player");
	player->Initialize();

	auto skills = SkillManager::GetInstance().GetUniqueRandomSkillTypes(player.get(), SkillType::ACTIVE, 3);

	vector<string> options;
	int skillSize = skills.size();

	for (int i = 0; i < skillSize; i++)
	{
		shared_ptr<Skill> skill = SkillManager::GetInstance().CreateSkillFromType(skills[i], player.get());
		options.push_back(to_string(i + 1) + ", " + skill->GetSkillData().skillName);
	}

	int input = InputManagerSystem::GetInput<int>("스킬을 고르세요.", options, RangeValidator<int>(1, skillSize));

	auto skillManager = SkillManager::GetInstance();

	skillManager.AddSelectSkillToCharacter(skills[input - 1], player.get());
}

void SystemContext::OnEvent(const std::shared_ptr<IEvent> ev)
{
	if (auto move = std::dynamic_pointer_cast<IMoveSystemEvent>(ev))
	{
		MoveSystem(move->to, move->from);
	}
	else if (auto create = std::dynamic_pointer_cast<ICharacterCreateEvent>(ev))
	{
		CreateCharacter(create->name);
	}
	else if (auto gameOver = std::dynamic_pointer_cast<IPlayerDefeatEvent>(ev))
	{
		player.reset();
	}

	Publish(ev);
}


