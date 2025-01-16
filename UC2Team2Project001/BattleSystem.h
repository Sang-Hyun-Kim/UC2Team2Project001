#pragma once
#include "GameSystem.h"
class Character;
class Monster;
class URewardEventManagerSystem;
class UTurnEventManager;

class BattleSystem : public GameSystem
{
public:
	BattleSystem();

	virtual void EnterSystem() override;
	//virtual void ChangeState() override;
	void MainMenu();
	void Attack();
	void DisplayStat();
	void UseItem();
	void NextStage();
	void GameOver();
	void StartTurn();

	inline SystemType GetSystemType() override { return SystemType::BATTLE;}
	void OnEvent(const std::shared_ptr<IEvent> ev) override;

	virtual string GetSystemName() override { return "배틀"; }
private:
	void GetReward();

	vector<Character*> activeCharacters;

	shared_ptr<Monster> monster;
	shared_ptr<URewardEventManagerSystem> rewardSystem;
	shared_ptr<UTurnEventManager> turnSystem;

	int monsterCount = 0;
};
