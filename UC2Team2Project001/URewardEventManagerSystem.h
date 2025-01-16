#pragma once
#include "EventManagerSystem.h"

class URewardEventManagerSystem : public IEventManagerSystem
{
public:
	void OnEvent(std::shared_ptr<IEvent> ev) override;


private:

};

