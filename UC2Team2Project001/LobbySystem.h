#pragma once
#include "GameSystem.h"


class LobbySystem : public GameSystem
{
public:

	LobbySystem();
	void EnterSystem() override;

	inline SystemType GetSystemType() override { return SystemType::LOBBY; }
	void OnEvent(const std::shared_ptr<IEvent> ev) override;

	void MainMenu();
	void CreatePlayerMenu();

	virtual string GetSystemName() override { return "로비"; };
private:
};