#pragma once

#include "Skill.h"

class LifeStealAttack : public ActiveSkill
{
public:
	LifeStealAttack(shared_ptr<Character> _owner);
};

