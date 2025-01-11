#pragma once

#include "EventManagerSystem.h"
#include <iostream>

class UIEventManagerSystem : public IEventManagerSystem
{
public:
	UIEventManagerSystem();

	virtual ~UIEventManagerSystem();

	virtual void OnEvent(const std::shared_ptr<IEvent>& ev) override;
};
