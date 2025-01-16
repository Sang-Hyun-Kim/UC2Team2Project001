#include "pch.h"
#include "URewardEventManagerSystem.h"
#include "ICharacterEventTypes.h"

void URewardEventManagerSystem::OnEvent(std::shared_ptr<IEvent> ev)
{
	
	
	if (auto dead = std::dynamic_pointer_cast<ICharacterDeadEvent>(ev))
	{
		dead->reward.DropGold;
		dead->reward.DropItem;
		
		// 스킬 추가
		//플레이어
	}
}