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
	//virtual void ChangeState() override;
	void MainMenu();
	void Attack();
	void DisplayStat();
	void UseItem();
	void NextStage();
	void GameOver();

	inline SystemType GetSystemType() override { return SystemType::BATTLE; }
	void OnEvent(const std::shared_ptr<IEvent>& ev) override;
private:
	shared_ptr<Monster> monster;

};
