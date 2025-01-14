#include "pch.h"
#include "SystemContext.h"
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
		if (dead->Reward.IsEmpty())
		{
			// 몬스터 출력, reward는 몬스터만 받으니까 몬스터가 죽은 경우 reward 획득을 출력하기
			dead->Reward.DropGold;
			dead->Reward.DropItem;
		}
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
		std::cout << "[UI] " << Defense->CharacterName << "이(가) " << Defense->DefenseValue << "만큼 방어했습니다!" << endl;
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
		std::cout << menuEvent->title << "\n";
		for (const string& option : menuEvent->options)
		{
			cout << option << "\n";
		}
		cout << menuEvent->inputText;
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
	else if (auto playerbattleattack = std::dynamic_pointer_cast<IBattleAttackEvent>(ev))
	{
		cout << "플레이어 공격 수행" << endl;
	}
	else if (auto playerbattlecheckstat = std::dynamic_pointer_cast<IBattleStatCheckEvent>(ev))
	{
		cout << "스탯을 확인합니다" << endl;
	}
	else if (auto playerbattleuseitem = std::dynamic_pointer_cast<IBattleUseItemEvent>(ev))
	{
		cout << "아이템을 사용합니다." << endl;
	}
	else if (auto gamedefeat = std::dynamic_pointer_cast<IPlayerDefeatEvent>(ev))
	{
		cout << "플레이어가 사망하였습니다.\n"<<"게임 로비로 귀환합니다." << endl;
		cout << "--------------------------------------------------\n"
			<< "                  게  임  패  배                   \n"
			<< "---------------------------------------------------" << endl;
	}
	else if (auto gameclear = std::dynamic_pointer_cast<IPlayerGameClearEvent>(ev))
	{
		cout << "보스 몬스터를 쓰러트렸습니다. 게임 클리어!!!" << endl;
		cout << "--------------------------------------------------\n"
			<< "                  게 임 클 리 어                   \n"
			<< "---------------------------------------------------" << endl;
 	}
	else if (auto gameclear = std::dynamic_pointer_cast<IPlayerGetItemEvent>(ev))
	{
		cout << "아이템을 획득했습니다." << endl;
	}
	else if (auto playerlevelup = std::dynamic_pointer_cast<ILevelUpEvent>(ev))
	{
		cout <<"--------------------------------------------------\n"
			<< "                플 레 이 어 레 벨 업              \n"
			<< "---------------------------------------------------" << endl;
	}
	else if (auto stageclear = std::dynamic_pointer_cast<IPlayerStageClearEvent>(ev))
	{
		cout << "몬스터 사망으로 스테이지 클리어" << endl;
	}
	else if (auto create = std::dynamic_pointer_cast<ICharacterCreateEvent>(ev))
	{
		cout << "캐릭터 생성 완료" << endl;
	}
	else
	{
		std::cout << "[UI] 알 수 없는 이벤트.\n";
	}
}
