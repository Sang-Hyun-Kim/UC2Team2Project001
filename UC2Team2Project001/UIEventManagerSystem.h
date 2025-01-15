#pragma once

#include "EventManagerSystem.h"
#include <iostream>

class UIEventManagerSystem : public IEventManagerSystem
{
public:
	UIEventManagerSystem();

	virtual ~UIEventManagerSystem();

	virtual void OnEvent(std::shared_ptr<IEvent> ev) override;
	
};
