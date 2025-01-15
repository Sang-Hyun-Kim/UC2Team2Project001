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
#include "CombatComponent.h"
#include "USkillComponent.h"
#include "UTurnEventManager.h"
#include "UStatusComponent.h"
#include "LifeStealAttack.h"

// 게임 시스템 코드가 돌아갈 main 함수

using namespace std;

int main()
{
	// 랜덤 함수 시드 설정
	srand((unsigned int)time(NULL));
	

	// GlobalEventManager 싱글톤 인스턴스 가져오기 //지우지마세요
	GlobalEventManager& eventManager = GlobalEventManager::Get();

	//// UI 시스템 생성  //지우지 마세요
	auto UISystem = std::make_shared<UIEventManagerSystem>();
	eventManager.Subscribe(UISystem);

	auto TurnEventManager = std::make_shared<UTurnEventManager>();
	eventManager.Subscribe(TurnEventManager);

	//GSystemContext->currentSystem = GLobbySystem;


	//while (true)
	//{
	//	GSystemContext->currentSystem->Update(); // Update()로 변경해야함
	//}


#pragma region 캐릭터 테스트 예시 코드

	//Player* player = new Player("Player");
	//Monster* monster = new Monster(1);

	//TurnEventManager->BeginTurn();

	//player->StatusComponent->AddState(make_shared<BurnState>(3, 10));

	//player->combatManager->Attack();
	//monster->combatManager->Attack();

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
	//	GSystemContext->currentSystem->Update(); // Update()로 변경해야함
	//}

	//delete player;
	//delete monster;

#pragma region 스킬 사용 예제

	shared_ptr<Player> player = make_shared<Player>("Player");
	player->Initialize();

	shared_ptr<Monster> monster = make_shared<Monster>();
	monster->Initialize();
	monster->combatManager->SetTarget(player.get());

	shared_ptr<LifeStealAttack> newLifeStealAttack = make_shared<LifeStealAttack>(monster.get());
	monster->skillManager->AddSkill(newLifeStealAttack);
	
	monster->skillManager->UseSkill(SkillType::ACTIVE, "흡혈 공격");

#pragma endregion

	//몬스터가 소멸되고 -> 몬스터가 스텟매니저 스킬매니저

	
	
}