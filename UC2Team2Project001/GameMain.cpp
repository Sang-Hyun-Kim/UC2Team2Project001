#include "pch.h"
#include "GameSystem.h"
#include "GlobalEventManager.h"
#include "IEventTypes.h"
#include "Character.h"
#include "IStrategy.h"
#include <filesystem>
#include "UIEventManagerSystem.h"
#include "Inventory.h"
#include "ItemManager.h"
// 게임 시스템 코드가 돌아갈 main 함수

int main()
{
	// 랜덤 함수 시드 설정
	//srand(time(NULL));

	//// GlobalEventManager 싱글톤 인스턴스 가져오기
	//GlobalEventManager& eventManager = GlobalEventManager::Get();

	//// UI 시스템 생성
	//auto UISystem = std::make_shared<UIEventManagerSystem>();
	//eventManager.Subscribe(UISystem);


	////std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;


	//Character player("Player");
	//Character goblin("Goblin");

	//// 공격 전략 설정
	//player.SetAttackStrategy(std::make_shared<BasicAttackStrategy>());
	//player.Attack(&goblin);
	
	Inventory inv(new Character("Player"));

	

	inv.addItem(ItemManager::GetInstance().getRandomItem());
	inv.addItem(ItemManager::GetInstance().getRandomItem());
	inv.addItem(ItemManager::GetInstance().getRandomItem());
	inv.addItem(ItemManager::GetInstance().getRandomItem());
	inv.addGold(50);

	inv.displayInventory();
	
	inv.useItem(0);
	inv.useItem(0);
	inv.useItem(0);
	inv.removeGold(10);
	inv.displayInventory();
	
	/*GLobbySystem->CreatePlayer();
	GLobbySystem->PlayerMove();
	GBattleSystem->EnterSystem();*/
}
