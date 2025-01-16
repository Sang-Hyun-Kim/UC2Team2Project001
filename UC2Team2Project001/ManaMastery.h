#pragma once

#include "Skill.h"

class ManaMastery : public PassiveSkill
{
public:
	ManaMastery(Character* _owner);

	virtual void HandlePassiveEvent(std::shared_ptr<IEvent> _event)override;
};
