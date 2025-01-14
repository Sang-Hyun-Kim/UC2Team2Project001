#pragma once
#include "InputManagerSystem.h"
#include "SystemContext.h"

class GameSystem
{
public:
	inline virtual SystemType GetSystemType() = 0;

	virtual void EnterSystem() = 0; // 시스템이 시작될 때 수행될 함수(Initialize)
	virtual void Update() = 0; // system의 로직 수행을 수행하는 함수, 반복
	void ExitSystem(SystemType nextType); // 시스템을 나가야할 때 수행할 함수
	virtual ~GameSystem() {};
};