#pragma once
#include "pch.h"
#include "BattleSystem.h"

class BattleStartTurnState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->StartTurn();
		}
	}
};


class BattleMainState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->MainMenu();
		}
	}
};

class BattleAttackState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->Attack();
		}
	}
};

class BattleDisplayState : public ISystemState
{
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->DisplayStat();
		}
	}
};

class BattleUseItemState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->UseItem();
		}
	}
};

class BattleNextStageState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->NextStage();
		}
	}
};

class BattleGameOverState: public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->GameOver();
		}
	}
};