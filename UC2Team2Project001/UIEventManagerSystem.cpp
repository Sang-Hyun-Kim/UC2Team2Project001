#include "pch.h"
#include "SystemContext.h"
#include "UIEventManagerSystem.h"
#include "IEventTypes.h"  
#include "GlobalEventManager.h"
#include "Item.h"
#include "CharacterTypes.h"

#include "IItemEventTypes.h"
#include "ICombatEventTypes.h"
#include "ICharacterEventTypes.h"
#include "IInputEventTypes.h"
#include "ISystemTypes.h"

UIEventManagerSystem::UIEventManagerSystem()
{
	// ICharacterDamagedEvent를 처리하는 핸들러 등록
	Subscribe<ICharacterDamagedEvent>([](ICharacterDamagedEvent* e)
		{
			std::cout << "[UI] " << e->characterName << "님이 " << e->damage << "의 피해를 입었습니다.\n";
		});

	// ICharacterDeadEvent를 처리하는 핸들러 등록
	Subscribe<ICharacterDeadEvent>([](ICharacterDeadEvent* e)
		{
			if (!e->reward.IsEmpty())
			{
				std::cout << "[" << e->characterName << "]의 " << e->reward.DropGold << "를 획득했습니다.\n";
				std::cout << "[" << e->characterName << "]의 " << e->reward.DropItem << "를 획득했습니다.\n";
			}
			std::cout << "[UI] " << e->characterName << "님이 사망했습니다.\n";
		});

	// IItemPurchasedEvent를 처리하는 핸들러 등록
	Subscribe<IItemPurchasedEvent>([](IItemPurchasedEvent* e)
		{
			std::cout << "[UI] " << e->buyerName << "님이 " << e->itemName << "을(를) " << e->cost << "에 구매했습니다.\n";
		});

	// ICharacterAttackEvent를 처리하는 핸들러 등록
	Subscribe<ICharacterAttackEvent>([](ICharacterAttackEvent* e)
		{
			std::cout << "[UI] " << e->characterName << "이(가) 공격했습니다!\n";
		});

	// ICharacterDefenseEvent를 처리하는 핸들러 등록
	Subscribe<ICharacterDefenseEvent>([](ICharacterDefenseEvent* e)
		{
			std::cout << "[UI] " << e->characterName << "이(가) " << e->defenseValue << " 만큼 방어했습니다!\n";
		});

	// IItemSoldEvent를 처리하는 핸들러 등록
	Subscribe<IItemSoldEvent>([](IItemSoldEvent* e)
		{
			std::cout << "[UI] " << e->sellerName << "님이 " << e->itemName << "을(를) " << e->cost << "에 판매했습니다.\n";
		});

	// IMoveEvent를 처리하는 핸들러 등록
	Subscribe<IMoveEvent>([](IMoveEvent* e)
		{
			std::cout << "[UI] " << e->from << "에서 " << e->to << "로 이동했습니다.\n";
		});

	// IDisplayMenuEvent를 처리하는 핸들러 등록
	Subscribe<IDisplayMenuEvent>([](IDisplayMenuEvent* e)
		{
			system("cls");
			std::cout << e->title << "\n";
			for (const auto& option : e->options)
			{
				std::cout << option << "\n";
			}
			std::cout << e->inputText;
		});

	// IWrongInputEvent를 처리하는 핸들러 등록
	Subscribe<IWrongInputEvent>([](IWrongInputEvent*)
		{
			std::cout << "잘못된 입력입니다.\n";
		});

	// IGameExitEvent를 처리하는 핸들러 등록
	Subscribe<IGameExitEvent>([](IGameExitEvent*)
		{
			std::cout << "게임을 종료합니다.\n";
			exit(1);
		});

	// IGameStartEvent를 처리하는 핸들러 등록
	Subscribe<IGameStartEvent>([](IGameStartEvent*)
		{
			std::cout << "게임을 시작합니다.\n";
		});

	// IPlayerBattleAttackEvent를 처리하는 핸들러 등록
	Subscribe<IPlayerBattleAttackEvent>([](IPlayerBattleAttackEvent*)
		{
			std::cout << "플레이어 공격 수행\n";
		});

	// IBattleUseItemEvent를 처리하는 핸들러 등록
	Subscribe<IBattleUseItemEvent>([](IBattleUseItemEvent*)
		{
			std::cout << "아이템을 사용합니다.\n";
		});

	// IPlayerDefeatEvent를 처리하는 핸들러 등록
	Subscribe<IPlayerDefeatEvent>([](IPlayerDefeatEvent*)
		{
			std::cout << "플레이어가 사망하였습니다.\n게임 로비로 귀환합니다.\n";
			std::cout << "--------------------------------------------------\n"
				<< "                  게  임  패  배                   \n"
				<< "---------------------------------------------------\n";
		});

	// IPlayerGameClearEvent를 처리하는 핸들러 등록
	Subscribe<IPlayerGameClearEvent>([](IPlayerGameClearEvent*)
		{
			std::cout << "보스 몬스터를 쓰러트렸습니다. 게임 클리어!!!\n";
			std::cout << "--------------------------------------------------\n"
				<< "                  게 임 클 리 어                   \n"
				<< "---------------------------------------------------\n";
		});

	// ICharacterLevelUpEvent를 처리하는 핸들러 등록
	Subscribe<ICharacterLevelUpEvent>([](ICharacterLevelUpEvent*)
		{
			std::cout << "--------------------------------------------------\n"
				<< "                플 레 이 어 레 벨 업              \n"
				<< "---------------------------------------------------\n";
		});

	// IPlayerStageClearEvent를 처리하는 핸들러 등록
	Subscribe<IPlayerStageClearEvent>([](IPlayerStageClearEvent*)
		{
			std::cout << "몬스터 사망으로 스테이지 클리어\n";
		});


}

UIEventManagerSystem::~UIEventManagerSystem()
{
}

void UIEventManagerSystem::OnEvent(std::shared_ptr<IEvent> ev)
{
	Publish(ev);
}


