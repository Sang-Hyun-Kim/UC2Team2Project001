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

	IMoveEvent(const std::string& to, const std::string& from) :to(to), from(from) {}
};

// 게임 종료 이벤트
class IGameExitEvent : public IEvent
{
public:
	IGameExitEvent() {}
};
// 게임 종료 이벤트
class IGameStartEvent : public IEvent
{
public:
	IGameStartEvent() {}
};
