#pragma once

#include "EventManagerSystem.h"
#include <iostream>

class UIEventManagerSystem : public EventManagerSystem
{
public:
	UIEventManagerSystem() = default;
	virtual ~UIEventManagerSystem() = default;

	virtual void OnEvent(const std::shared_ptr<IEvent>& ev) override;
};
