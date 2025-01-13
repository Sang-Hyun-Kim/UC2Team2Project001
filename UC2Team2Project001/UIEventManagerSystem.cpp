#include "pch.h"
#include "UIEventManagerSystem.h"
#include "IEventTypes.h"  

void UIEventManagerSystem::OnEvent(const std::shared_ptr<IEvent>& ev)
{
	// 예시: 캐릭터 데미지, 사망, 구매 이벤트 처리
	if (auto dmg = std::dynamic_pointer_cast<ICharacterDamagedEvent>(ev))
	{
		std::cout << "[UI] " << dmg->CharacterName << "님이 "
			<< dmg->Damage << "의 피해를 입었습니다.\n";
	}
	else if (auto dead = std::dynamic_pointer_cast<ICharacterDeadEvent>(ev))
	{
		std::cout << "[UI] " << dead->CharacterName << "님이 사망했습니다.\n";
	}
	else if (auto itemEvent = std::dynamic_pointer_cast<IItemPurchasedEvent>(ev))
	{
		std::cout << "[UI] " << itemEvent->BuyerName << "님이 "
			<< itemEvent->ItemName << "을(를) "
			<< itemEvent->Cost << "에 구매했습니다.\n";
	}
	else if (auto sellEvent = std::dynamic_pointer_cast<IItemSoldEvent>(ev))
	{
		std::cout << "[UI] " << itemEvent->BuyerName << "님이 "
			<< itemEvent->ItemName << "을(를) "
			<< itemEvent->Cost << "에 판매했습니다.\n";
	}
	else if (auto moveEvent = std::dynamic_pointer_cast<IMoveEvent>(ev))
	{
		std::cout << "[UI] " << moveEvent->from << "에서 "
			<< moveEvent->to << "로 이동했습니다.\n";
	}
	else if (auto menuEvent = std::dynamic_pointer_cast<IDisplayMenuEvent>(ev))
	{
		//system("cls");  //콘솔창 클리어 함수 (오류 메시지까지 보여주려면 delay 함수 필요)
		std::cout << menuEvent->title << "\n";
		for (const string& option : menuEvent->options)
		{
			cout << option << "\n";
		}
		cout << "input: ";
	}
	else if (auto wrongInputEvent = std::dynamic_pointer_cast<IWrongInputEvent>(ev))
	{
		cout << "잘못된 입력입니다.\n";
	}
	else if (auto gameexitEvent = std::dynamic_pointer_cast<IGameExitEvent>(ev))
	{
		cout << "게임을 종료합니다." << endl;
		exit(1);
	}
	else if (auto gamestartEvent = std::dynamic_pointer_cast<IGameStartEvent>(ev))
	{
		cout << "게임을 시작합니다." << endl;
	}
	else
	{
		std::cout << "[UI] 알 수 없는 이벤트.\n";
	}
}
