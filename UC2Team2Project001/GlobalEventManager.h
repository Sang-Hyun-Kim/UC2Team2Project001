#pragma once

#include <vector>
#include <memory>
#include "EventManagerSystem.h"

class IEvent;

class GlobalEventManager
{
private:
	GlobalEventManager();
	~GlobalEventManager();

public:
	static GlobalEventManager& Get()
	{
		static GlobalEventManager instance;

		return instance;
	}

	// 복사/대입 불가
	GlobalEventManager(const GlobalEventManager&) = delete;

	GlobalEventManager& operator=(const GlobalEventManager&) = delete;

	// 구독 등록
	int Subscribe(const std::shared_ptr<IEventManagerSystem>& _system);

	// 구독 해제
	void Unsubscribe(int _subscriptionId);

	// 모든 구독자에게 이벤트 알림
	void Notify(std::shared_ptr<IEvent> _callEv);

private:
	int nextId = 1;

	vector<shared_ptr<IEventManagerSystem>> _listeners;
};
