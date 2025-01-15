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
#include "BashAttack.h"
#include "ShieldAttack.h"
#include "MentalDiscipline.h"
#include "OnePointAttack.h"
#include "PoisonedBlade.h"
#include "PoisonInfusion.h"
#include "PoisonFog.h"
#include "PoisonTrigger.h"
#include "Plague.h"
#include "ICombatEventTypes.h"


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



	//player->StatusComponent->AddState(make_shared<BurnState>(3, 10));

	//player->combatManager->Attack();
	//monster->combatManager->Attack();



	

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

	//타겟 설정합니다
	monster->combatManager->SetTarget(player.get());
	player->combatManager->SetTarget(monster.get());

	std::vector<Character*> battleCharacters;
	battleCharacters.push_back(player.get());
	battleCharacters.push_back(monster.get());

	/*shared_ptr<LifeStealAttack> newLifeStealAttack = make_shared<LifeStealAttack>(monster.get());
	monster->skillManager->AddSkill(newLifeStealAttack);*/


	TurnEventManager->BeginTurn();

	shared_ptr<PoisonedBlade> newPoisonedBlade= make_shared<PoisonedBlade>(monster.get());
	monster->skillManager->AddSkill(newPoisonedBlade);

	shared_ptr<PoisonInfusion> newPoisonInfusion = make_shared<PoisonInfusion>(monster.get());
	monster->skillManager->AddSkill(newPoisonInfusion);

	shared_ptr<PoisonFog> newPoisonFog = make_shared<PoisonFog>(monster.get());
	monster->skillManager->AddSkill(newPoisonFog);

	shared_ptr<PoisonTrigger> newPoisonTrigger = make_shared<PoisonTrigger>(monster.get());
	monster->skillManager->AddSkill(newPoisonTrigger);

	//패시브
	shared_ptr<Plague> newPlague = make_shared<Plague>(player.get());
	player->skillManager->AddSkill(newPlague);
	
	player->combatManager->Attack();
	auto playerAttackEvent = make_shared<IPlayerBattleAttackEvent>();
	eventManager.Notify(playerAttackEvent);

	/*monster->skillManager->UseSkill(SkillType::ACTIVE, "독이 묻은 칼");
	monster->skillManager->UseSkill(SkillType::ACTIVE, "맹독 부여");
	monster->skillManager->UseSkill(SkillType::ACTIVE, "독 안개");
	monster->skillManager->UseSkill(SkillType::ACTIVE, "독 격발");*/

	TurnEventManager->EndTurn(battleCharacters);

#pragma endregion
}