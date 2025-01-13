#include "pch.h"
#include "UIEventManagerSystem.h"
#include "IEventTypes.h"  
#include "GlobalEventManager.h"
#include "Item.h"
#include "CharacterTypes.h"

UIEventManagerSystem::UIEventManagerSystem()
{
}

UIEventManagerSystem::~UIEventManagerSystem()
{
}

void UIEventManagerSystem::OnEvent(const std::shared_ptr<IEvent>& ev)
{
	// 예시: 캐릭터 데미지, 사망, 구매 이벤트 처리
	if (auto dmg = std::dynamic_pointer_cast<ICharacterDamagedEvent>(ev))
	{
		std::cout << "[UI] " << dmg->CharacterName << "님이 " << dmg->Damage << "의 피해를 입었습니다.\n";
	}
	else if (auto dead = std::dynamic_pointer_cast<ICharacterDeadEvent>(ev))
	{
		std::cout << "[UI] " << dead->CharacterName << "님이 사망했습니다.\n";
	}
	else if (auto itemEvent = std::dynamic_pointer_cast<IItemPurchasedEvent>(ev))
	{
		std::cout << "[UI] " << itemEvent->BuyerName << "님이 " << itemEvent->ItemName << "을(를) " << itemEvent->Cost << "에 구매했습니다.\n";
	}
	else if (auto Attack = std::dynamic_pointer_cast<ICharacterAttackEvent>(ev))
	{
		std::cout << "[UI] " << Attack->CharacterName << "이(가) 공격했습니다!\n";
	}
	else if (auto Defense = std::dynamic_pointer_cast<ICharacterDefenseEvent>(ev))
	{
		std::cout << "[UI] " << Defense->CharacterName << "이(가)" << Defense->DefenseValue << " 만큼 방어했습니다!" << endl;
	}
	else
	{
		std::cout << "[UI] 알 수 없는 이벤트.\n";
	}
}
