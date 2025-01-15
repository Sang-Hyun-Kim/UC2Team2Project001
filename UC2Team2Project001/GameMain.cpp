#include "pch.h"
#include "GameSystem.h"
#include "GlobalEventManager.h"
#include "IEventTypes.h"
#include "Character.h"
#include "IStrategy.h"
#include <filesystem>
#include "UIEventManagerSystem.h"
#include "Monster.h"
#include "StatComponent.h"
#include "ItemManager.h"
#include "Item.h"
#include <unordered_map>
#include "Inventory.h"
#include "ShopSystem.h"
#include "InputManagerSystem.h"
#include "CommandTypes.h"
#include "PlayerCharacter.h"
#include "UTurnEventManager.h"
#include "UStatusComponent.h"


// 게임 시스템 코드가 돌아갈 main 함수

using namespace std;

int main()
{
	// 랜덤 함수 시드 설정
	//srand(time(NULL));

	// GlobalEventManager 싱글톤 인스턴스 가져오기 //지우지마세요
	GlobalEventManager& eventManager = GlobalEventManager::Get();

	// UI 시스템 생성  //지우지 마세요
	auto UISystem = std::make_shared<UIEventManagerSystem>();
	eventManager.Subscribe(UISystem);

	auto TurnEventManager = std::make_shared<UTurnEventManager>();
	eventManager.Subscribe(TurnEventManager);

	GSystemContext->currentSystem = GLobbySystem;


	//while (true)
	//{
	//	GSystemContext->currentSystem->Update(); // Update()로 변경해야함
	//}


#pragma region 캐릭터 테스트 예시 코드

	Player* player = new Player("Player");
	Monster* monster = new Monster(1);

	//TurnEventManager->BeginTurn();

	//player->StatusComponent->AddState(make_shared<BurnState>(3, 10));

	player->Attack(monster);
	monster->Attack(player);

	//std::vector<Character*> battleCharacters;
	//battleCharacters.push_back(player);
	//battleCharacters.push_back(monster);

	//TurnEventManager->EndTurn(battleCharacters);


	
	

	//player->InventoryComponent->addItem(ItemManager::GetInstance().getRandomItem());
	//player->InventoryComponent->addItem(ItemManager::GetInstance().getRandomItem());
	//player->InventoryComponent->addItem(ItemManager::GetInstance().getRandomItem());
	//player->InventoryComponent->addItem(ItemManager::GetInstance().getRandomItem());
	//player->InventoryComponent->addGold(50);

	//inv.displayInventory();

	//inv.useItem(0);
	//inv.useItem(0);
	//inv.useItem(0);
	//inv.removeGold(10);

	//player->InventoryComponent->displayInventory();
	//player->UseItem(0, player);

	
	//BurnState burnState(3, 10); // 3턴 동안 매 턴 10 데미지

	//while (!burnState.IsExpired())
	//{
	//	burnState.ApplyEffect(player);
	//}

	//while (!monster->StatManager->IsDead())
	//{
	//	player->Attack(monster);
	//	monster->Attack(player);
	//}

	//cout << player->GetName() << "가 " << monster->CharacterReward.DropGold << "골드를 획득했습니다.\n";
	
	//// 아이템이 있을 경우
	//if (monster->CharacterReward.DropItem != nullptr)
	//{
	//	// 현재 아이템 이름이 설정되어 있지 않아서 빈칸으로 출력됨
	//	cout << player->GetName() << "가 " << monster->CharacterReward.DropItem.get()->getName() << "을(를) 획득했습니다.";
	//}





	delete player;
	delete monster;

#pragma endregion
	
	/*GLobbySystem->CreatePlayer();
	GLobbySystem->PlayerMove();
	GBattleSystem->EnterSystem();*/
	
}


//현재 디렉토리 출력
	//std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;