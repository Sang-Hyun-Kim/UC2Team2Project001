#pragma once

#include <functional>
#include <typeindex>
#include <memory>
#include <unordered_map>
#include <vector>
#include "IEventTypes.h"

class IEvent;

using EventHandlerFunc = std::function<void(IEvent*)>;
using HandlerList = std::vector<EventHandlerFunc>;

class IEventManagerSystem
{
public:
	virtual ~IEventManagerSystem() = default;

	virtual void OnEvent(std::shared_ptr<IEvent> ev) = 0;

	int GetID() const { return ID; }

	void SetID(int newId) { ID = newId; }

	template<typename T>
	int Subscribe(std::function<void(T*)> handler)
	{
		EventHandlerFunc wrapper = [handler](IEvent* ev) {
			handler(static_cast<T*>(ev));
			};

		HandlerList& list = handlers[std::type_index(typeid(T))];
		list.push_back(wrapper);
		return ++NextId;
	}

	void Publish(std::shared_ptr<IEvent> ev)
	{
		auto it = handlers.find(std::type_index(typeid(*ev)));
		if (it != handlers.end())
		{
			for (auto& func : it->second)
			{
				func(ev.get());
			}
		}
	}

private:
	int ID = -1;
	int NextId = 0;
	std::unordered_map<std::type_index, HandlerList> handlers;
};
