#pragma once

#include "Skill.h"
#include "CombatComponent.h"



// 빙하의 파편 스킬 클래스 정의
class GlacialShard : public ActiveSkill
{
public:
	GlacialShard(Character* _owner);
};
