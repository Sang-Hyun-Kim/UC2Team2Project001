#pragma once
#include "GameSystem.h"


class LobbySystem : public GameSystem
{
public:

	LobbySystem();
	void EnterSystem() override; // 로비 실행후 동작

	//virtual void Update();

	inline SystemType GetSystemType() override { return SystemType::LOBBY; }
	void OnEvent(const std::shared_ptr<IEvent> ev) override;

	void MainMenu();
	void CreatePlayerMenu();
private:
};