#pragma once

#include "EventManagerSystem.h"
#include <memory>
#include <vector>

class Character;

/**
 * @brief 게임의 턴 기반 진행을 관리하는 매니저
 *
 * - BeginTurn(): 턴 시작 시 호출
 * - ExecuteTurnActions(): 실제 턴 내의 전투/행동 로직 처리
 * - EndTurn(): 턴 종료 시 처리(상태 갱신 등)
 */
class UTurnEventManager : public IEventManagerSystem
{
public:
	UTurnEventManager();

	virtual ~UTurnEventManager();

	virtual void OnEvent(std::shared_ptr<IEvent> ev)  override;
	

	// 턴 진행
	void BeginTurn();

	void ExecuteTurnActions(Character* Player, Character* Monster);

	void EndTurn(std::vector<Character*>& AllCharacters);


	//완전끝났을때
	void TurnReset();

private:
	int currentTurn;
};
