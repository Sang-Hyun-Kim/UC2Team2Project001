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

#include "InputManagerSystem.h"

#include "ConsoleLayout.h"

UIEventManagerSystem::UIEventManagerSystem()
{
	// ICharacterDamagedEvent를 처리하는 핸들러 등록
	Subscribe<ICharacterDamagedEvent>([](ICharacterDamagedEvent* e)
		{
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[Battle] " + e->characterName + "님이 " + to_string(e->damage) + "의 피해를 입었습니다.");
			Delay(1);
		});

	// ICharacterDeadEvent를 처리하는 핸들러 등록
	Subscribe<ICharacterDeadEvent>([](ICharacterDeadEvent* e)
		{
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[Battle] " + e->characterName + "님이 사망했습니다.");
			Delay(1);

			if (!e->reward.IsEmpty())
			{
				ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[System] " + e->characterName + "에게서 " + to_string(e->reward.dropGold) + " Gold를 획득했습니다.");
				Delay(1);

				if (e->reward.dropItem != nullptr)
				{
					ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[System] " + e->reward.dropItem->getName() + "를 획득했습니다.");
				}
			}
		});

	// IItemPurchasedEvent를 처리하는 핸들러 등록
	Subscribe<IItemPurchasedEvent>([](IItemPurchasedEvent* e)
		{
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[Shop] " + e->buyerName + "님이 " + e->itemName + "을(를) " + to_string(e->cost) + "에 구매했습니다.");
		});

	// ICharacterAttackEvent를 처리하는 핸들러 등록
	Subscribe<ICharacterAttackEvent>([](ICharacterAttackEvent* e)
		{
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[Battle] " + e->characterName + "이(가) 공격했습니다!");
			Delay(0, 900);
		});

	// ICharacterDefenseEvent를 처리하는 핸들러 등록
	Subscribe<ICharacterDefenseEvent>([](ICharacterDefenseEvent* e)
		{
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[Battle] " + e->characterName + "이(가) " + to_string(e->defenseValue) + " 만큼 방어했습니다!");
			Delay(0, 900);
		});

	// IItemSoldEvent를 처리하는 핸들러 등록
	Subscribe<IItemSoldEvent>([](IItemSoldEvent* e)
		{
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[Battle] " + e->sellerName + "님이 " + e->itemName + "을(를) " + to_string(e->cost) + "에 판매했습니다.");
		});

	// IMoveEvent를 처리하는 핸들러 등록
	Subscribe<IMoveSystemEvent>([](IMoveSystemEvent* e)
		{
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[System] " + e->fromName + "에서 " + e->toName + "로 이동했습니다.");
			Delay(1);
			ConsoleLayout::GetInstance().AllClear();
		});

	// IDisplayMenuEvent를 처리하는 핸들러 등록
	Subscribe<IDisplayMenuEvent>([](IDisplayMenuEvent* e)
		{
			ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::RightBottom);

			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::RightBottom, e->title);

			for (const auto& option : e->options)
			{
				ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::RightBottom, option);
			}

			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::RightBottom, e->inputText);
		});

	// IWrongInputEvent를 처리하는 핸들러 등록
	Subscribe<IWrongInputEvent>([](IWrongInputEvent*)
		{
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::RightBottom, "[System] 잘못된 입력입니다.");
			InputManagerSystem::PauseUntilEnter();
		});

	// IGameExitEvent를 처리하는 핸들러 등록
	Subscribe<IGameExitEvent>([](IGameExitEvent*)
		{
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[System] 게임을 종료합니다.");
			exit(1);
		});

	// IGameStartEvent를 처리하는 핸들러 등록
	Subscribe<IGameStartEvent>([](IGameStartEvent*)
		{
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "[System] 게임을 시작합니다.");
			Delay(1);
			ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);
		});
	Subscribe<IPlayerAddSkillEvent>([](IPlayerAddSkillEvent* e)
		{
			if (e->bIsPlayer)
			{
				std::string skillNotify = "💎" + e->ownerName + "님이 " + e->skillName + "스킬 획득 성공";
				ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, skillNotify, true, ConsoleColor::LightBlue);
			}
		});

	// IPlayerBattleAttackEvent를 처리하는 핸들러 등록
	//Subscribe<IPlayerBattleAttackEvent>([](IPlayerBattleAttackEvent*)
	//	{
	//		std::cout << "플레이어 공격 수행\n";
	//	});

	// IBattleUseItemEvent를 처리하는 핸들러 등록
	//Subscribe<IBattleUseItemEvent>([](IBattleUseItemEvent*)
	//	{
	//		std::cout << "아이템을 사용합니다.\n";
	//	});

	// IPlayerDefeatEvent를 처리하는 핸들러 등록
	Subscribe<IPlayerDefeatEvent>([](IPlayerDefeatEvent*)
		{
			ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "플레이어가 사망하였습니다.\n게임 로비로 귀환합니다.");
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "--------------------------------------------------");
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "                  게  임  패  배                   ");
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "---------------------------------------------------");
			Delay(1);
			ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);
		});

	// IPlayerGameClearEvent를 처리하는 핸들러 등록
	Subscribe<IPlayerGameClearEvent>([](IPlayerGameClearEvent*)
		{
			ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "보스 몬스터를 쓰러트렸습니다. 게임 클리어!!!");
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "--------------------------------------------------");
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "                  게 임 클 리 어                   ");
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "---------------------------------------------------");
		});

	// ICharacterLevelUpEvent를 처리하는 핸들러 등록
	Subscribe<ICharacterLevelUpEvent>([](ICharacterLevelUpEvent*)
		{
			ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "--------------------------------------------------");
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "                플 레 이 어 레 벨 업              ");
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "---------------------------------------------------");
			Delay(1);
			ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);
		});
	Subscribe<IPauseEnterEvent>([](IPauseEnterEvent* ev)
		{
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::RightBottom, "계속하려면 엔터를 누르세요.");
		});
	// IPlayerStageClearEvent를 처리하는 핸들러 등록
	//Subscribe<IPlayerStageClearEvent>([](IPlayerStageClearEvent*)
	//	{
	//		//std::cout << "몬스터 사망으로 스테이지 클리어\n";
	//	});
}

UIEventManagerSystem::~UIEventManagerSystem()
{
}

void UIEventManagerSystem::OnEvent(std::shared_ptr<IEvent> ev)
{
	Publish(ev);
}


