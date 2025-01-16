#pragma once

#include "pch.h"
#include <string>
#include <memory>
#include "IEventTypes.h"

class IEnterEvent : public IEvent
{
	string paseName;

};

class IMoveEvent : public IEvent
{
public:
	std::string to;
	std::string from;

	IMoveEvent(const std::string& _to, const std::string& _from) :to(_to), from(_from)
	{
	}
};

// 게임 종료 이벤트
class IGameExitEvent : public IEvent
{
public:
	IGameExitEvent()
	{
	}
};

// 게임 종료 이벤트
class IGameStartEvent : public IEvent
{
public:
	IGameStartEvent() 
	{
	}
};

// 턴 시작 이벤트
class ITurnStart : public IEvent
{
public:
	ITurnStart() 
	{
	}
};

// 매 턴 끝날 때마다 호출되는 이벤트
class ITurnEndEvent : public IEvent
{
public:
	ITurnEndEvent(int _currentTurn)  : currentTurn(_currentTurn)
	{
	}

public:
	int currentTurn = 1;
};
