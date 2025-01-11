#include "pch.h"
#include "GameSystem.h"
#include "Character.h"
#include "IStrategy.h"
#include <filesystem>
#include "GlobalEventManager.h"
#include "UIEventManagerSystem.h"

// 게임 시스템 코드가 돌아갈 main 함수

int main()
{
	// GlobalEventManager 싱글톤 인스턴스 가져오기
	GlobalEventManager& eventManager = GlobalEventManager::Get();

	// UI 시스템 생성
	auto UISystem = std::make_shared<UIEventManagerSystem>();
	eventManager.Subscribe(UISystem);


	//std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;


	Character player("Player");
	Character goblin("Goblin");

	// 공격 전략 설정
	player.SetAttackStrategy(std::make_unique<SimpleAttackStrategy>());
	player.Attack(&goblin);

	/*GLobbySystem->CreatePlayer();
	GLobbySystem->PlayerMove();
	GBattleSystem->EnterSystem();*/
}
