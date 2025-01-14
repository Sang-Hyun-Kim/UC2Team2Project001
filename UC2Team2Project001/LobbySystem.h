#pragma once
#include "GameSystem.h"


class LobbySystem : public GameSystem
{
	friend class SystemContext;

	enum LobbyState
	{
		MAIN = 0,
		START = 1,
		EXIT = 2
	};

	LobbySystem();
public:
	void EnterSystem() override; // 로비 실행후 동작

	virtual void Update();

	inline SystemType GetSystemType() override { return SystemType::LOBBY; }

private:
	void MainMenu();
	void StartMenu();
	int state = MAIN;
};