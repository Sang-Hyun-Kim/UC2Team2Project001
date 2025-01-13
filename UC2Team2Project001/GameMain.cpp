#include "pch.h"
#include "GameSystem.h"
#include "ShopSystem.h"
#include "InputManagerSystem.h"
#include "UIEventManagerSystem.h"
#include "CommandTypes.h"
// 게임 시스템 코드가 돌아갈 main 함수

int main()
{
	// GlobalEventManager 싱글톤 인스턴스 가져오기
	GlobalEventManager& eventManager = GlobalEventManager::Get();

	// UI 시스템 생성
	auto UISystem = std::make_shared<UIEventManagerSystem>();
	eventManager.Subscribe(UISystem);

	GSystemContext->currentSystem = GShopSystem;

	while (true)
	{
		GSystemContext->currentSystem->EnterSystem();
	}

	//GLobbySystem->CreatePlayer();
	//GLobbySystem->PlayerMove();
	//GBattleSystem->EnterSystem();


}
