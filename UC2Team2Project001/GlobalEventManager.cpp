#include "pch.h"
#include "GlobalEventManager.h"
#include "IEventTypes.h"

GlobalEventManager::GlobalEventManager() {}
GlobalEventManager::~GlobalEventManager() {}

int GlobalEventManager::Subscribe(const std::shared_ptr<IEventManagerSystem>& _system)
{
	int newId = nextId++;

	_system->SetID(newId);

	_listeners.push_back(_system);

	return newId;
}

void GlobalEventManager::Unsubscribe(int _subscriptionId)
{
	auto it = std::remove_if(_listeners.begin(), _listeners.end(),
		[_subscriptionId](const std::shared_ptr<IEventManagerSystem>& sys)
		{
			return (sys->GetID() == _subscriptionId);
		}
	);
	_listeners.erase(it, _listeners.end());
}

void GlobalEventManager::Notify(std::shared_ptr<IEvent> _callEv)
{
	for (int i = 0; i < _listeners.size(); i++)
	{
		_listeners[i].get()->OnEvent(_callEv);
	}	
}
