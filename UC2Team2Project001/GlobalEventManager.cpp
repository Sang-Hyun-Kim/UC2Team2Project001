#include "pch.h"
#include "GlobalEventManager.h"
#include "IEventTypes.h"

GlobalEventManager::GlobalEventManager() {}
GlobalEventManager::~GlobalEventManager() {}

int GlobalEventManager::Subscribe(const std::shared_ptr<IEventManagerSystem>& system)
{
	int newId = NextId++;

	system->SetID(newId);

	Listeners.push_back(system);

	return newId;
}

void GlobalEventManager::Unsubscribe(int subscriptionId)
{
	auto it = std::remove_if(Listeners.begin(), Listeners.end(),
		[subscriptionId](const std::shared_ptr<IEventManagerSystem>& sys)
		{
			return (sys->GetID() == subscriptionId);
		}
	);
	Listeners.erase(it, Listeners.end());
}

void GlobalEventManager::Notify(const std::shared_ptr<IEvent>& ev)
{
	// 모든 구독자에게 이벤트 알림 (다형성 호출)
	for (auto& system : Listeners)
	{
		system->OnEvent(ev);
	}
}
