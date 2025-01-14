#pragma once
#include "GameSystem.h"

class Monster;

class BattleSystem : public GameSystem
{
	friend class SystemContext;

	enum BattleState
	{
		MAINMENU = 0,
		ATTACK = 1,
		DISPLAYSTAT = 2,
		USEITEM = 3,
		NEXTSTAGE = 4,
		GAMEOVER = 5
	};

	BattleSystem();

public:
	virtual void EnterSystem() override;
	virtual void Update() override;

	void MainMenu();
	void Attack();
	void DisplayStat();
	void UseItem();
	void NextStage();
	void GameOver();

	inline SystemType GetSystemType() override { return SystemType::BATTLE; }
private:
	shared_ptr<Monster> monster;

	int state = MAINMENU;
};