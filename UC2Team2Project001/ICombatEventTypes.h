#pragma once

#include "IEventTypes.h"
#include <string>

using namespace std;

// ======================= 전투 관련 이벤트 =======================

// 전투 중 공격 이벤트
class IPlayerBattleAttackEvent : public IEvent
{
public:
	IPlayerBattleAttackEvent() {}
};

// 전투 중 아이템 사용 이벤트
class IBattleUseItemEvent : public IEvent
{
public:
	IBattleUseItemEvent() {}
};

// 플레이어가 사망하여 패배하는 이벤트
class IPlayerDefeatEvent : public IEvent
{
public:
	IPlayerDefeatEvent() {}
};

// 보스 몬스터를 처치하여 게임을 클리어하는 이벤트
class IPlayerGameClearEvent : public IEvent
{
public:
	IPlayerGameClearEvent() {}
};

// 일반 몬스터를 처치하여 스테이지를 클리어하는 이벤트
class IPlayerStageClearEvent : public IEvent
{
public:
	IPlayerStageClearEvent() {}
};


#pragma region 더미코드

// 전투 중 스탯 확인 이벤트
//class IBattleStatCheckEvent : public IEvent
//{
//public:
//	IBattleStatCheckEvent() {}
//};

#pragma endregion 더미코드