
#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(const std::string& InName): Character(InName)
	{
	}

	virtual ~Player() = default;

	// 플레이어만의 행동이나 정보
	// 예: 인벤토리, 골드, 경험치, 스킬 사용 등
	void AddToInventory(const std::string& item);
	// ...
};
