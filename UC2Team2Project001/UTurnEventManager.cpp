#include "pch.h"

#include "GlobalEventManager.h"
#include "UTurnEventManager.h"
#include "UStatusComponent.h"
#include "Character.h"
#include "ISystemTypes.h"
#include <iostream>
#include "USkillComponent.h"



UTurnEventManager::UTurnEventManager() : currentTurn(1) // 초기 턴
{
}

UTurnEventManager::~UTurnEventManager()
{
}

void UTurnEventManager::OnEvent(std::shared_ptr<IEvent> _event)
{
	// 필요에 따라 이벤트 처리
}

void UTurnEventManager::BeginTurn()
{
	std::cout << "================== Turn " << currentTurn << " 시작 ===================\n";

	auto turnStartEvent = make_shared<ITurnStart>();
	GlobalEventManager::Get().Notify(turnStartEvent);
}

void UTurnEventManager::ExecuteTurnActions(Character* _player, Character* _monster)
{
	
}

void UTurnEventManager::EndTurn(std::vector<Character*>& _allCharacters)
{
	// 모든 캐릭터(플레이어/몬스터 등)의 상태를 갱신
	for (auto& character : _allCharacters)
	{
		// (만약 턴마다 반복 적용이 필요하면 여기에 배치)
		if (character->statusManager)
		{
			// 1) 이번 턴에 적용된 상태 효과 적용
			character->statusManager->ApplyAllEffects();

			// 2) 턴 끝나고 상태 지속시간 차감
			character->statusManager->DecrementAllDurations();
			character->statusManager->RemoveExpiredStates();
		}

		// 3) 스킬 쿨다운 차감 (추가 예정)
		if (character->skillManager)
		{
			character->skillManager->AllReduceCooldown();
		}
	}
	
	auto newTurnEndEvent = make_shared<ITurnEndEvent>(currentTurn);
	GlobalEventManager::Get().Notify(newTurnEndEvent);

	// 턴 종료 출력
	std::cout << "================== Turn " << currentTurn << " 종료 ===================\n\n";

	// 다음 턴으로
	++currentTurn;
}

void UTurnEventManager::TurnReset()
{
	currentTurn = 1;
}
