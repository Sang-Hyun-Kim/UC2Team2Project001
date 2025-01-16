#pragma once
#include "InputManagerSystem.h"
#include "SystemContext.h"

class ISystemState
{
public:
	virtual ~ISystemState() = default;

	virtual void Excute(GameSystem* system) = 0;
};

class GameSystem : public IEventManagerSystem
{
public:
	inline virtual SystemType GetSystemType() = 0;
	
	virtual void EnterSystem() = 0; // 시스템이 시작될 때 수행될 함수(Initialize)
	void Update(); // system의 로직 수행을 수행하는 함수, 반복
	void ExitSystem(SystemType nextType); // 시스템을 나가야할 때 수행할 함수
	virtual ~GameSystem() {};
	//virtual void ChangeState() = 0;
	void SetState(shared_ptr<ISystemState> _state) { state = _state; }
protected:
	shared_ptr<ISystemState> state;
};