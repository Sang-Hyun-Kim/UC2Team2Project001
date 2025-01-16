#include "pch.h"
#include "URewardEventManagerSystem.h"
#include "ICharacterEventTypes.h"
#include "Skill.h"
#include "SkillManager.h"
#include "USkillComponent.h"
#include "SystemContext.h"

void URewardEventManagerSystem::OnEvent(std::shared_ptr<IEvent> _event)
{
	if (auto dead = std::dynamic_pointer_cast<ICharacterDeadEvent>(_event))
	{
		shared_ptr<Player> player = GSystemContext->GetPlayer();

		reward.gold = dead->reward.dropGold;
		reward.item = dead->reward.dropItem;
		reward.skillTypes = SkillManager::GetInstance().GetUniqueRandomSkillTypes((Character*)player.get(), SkillType::ACTIVE, 3);
		// 스킬 추가
		//플레이어
	}
}

void URewardEventManagerSystem::Initialize()
{
	reward.gold = 0;
	reward.item = nullptr;
	reward.skillTypes = {};
}
