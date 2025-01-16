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

	virtual void OnEvent(std::shared_ptr<IEvent> _event) = 0;

	int GetID() const
	{
		return id;
	}

	void SetID(int newId) 
	{ 
		id = newId; 
	}

	template<typename T>
	int Subscribe(std::function<void(T*)> _handler)
	{
		EventHandlerFunc wrapper = [_handler](IEvent* _event) {
			_handler(static_cast<T*>(_event));
			};

		HandlerList& list = handlers[std::type_index(typeid(T))];
		list.push_back(wrapper);
		return ++nextId;
	}

	void Publish(std::shared_ptr<IEvent> _event)
	{
		auto it = handlers.find(std::type_index(typeid(*_event)));
		if (it != handlers.end())
		{
			for (auto& func : it->second)
			{
				func(_event.get());
			}
		}
	}

private:
	int id = -1;
	int nextId = 0;
	std::unordered_map<std::type_index, HandlerList> handlers;
};
