#include "pch.h"
#include "GlobalEventManager.h"
#include "IEventTypes.h"
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
#include "SkillManager.h"
#include "Patience.h"
#include "Unbreakable.h"


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
	auto UTurnSystem = std::make_shared<UTurnEventManager>();
	eventManager.Subscribe(GSystemContext);
	eventManager.Subscribe(UISystem);
	eventManager.Subscribe(UTurnSystem);

	while (true)
	{
		GSystemContext->Update(); // Update()로 변경해야함
	}

#pragma region 스킬 매니저 테스트 코드
	 // 스킬 매니저 초기화
	//SkillManager& skillManager = SkillManager::GetInstance();

	// 테스트 캐릭터 생성
	/*shared_ptr<Player> player = make_shared<Player>("Player");
	player->Initialize();

	shared_ptr<Monster> monster = make_shared<Monster>();
	monster->Initialize();

	player->combatManager->SetTarget(monster.get());
	monster->combatManager->SetTarget(player.get());*/

	// 스킬 매니저를 통해 랜덤 액티브 스킬 추가
	//skillManager.AddRandomSkillToCharacter(player.get(), SkillType::ACTIVE);
	//skillManager.AddRandomSkillToCharacter(monster.get(), SkillType::ACTIVE);

	// 스킬 매니저를 통해 랜덤 패시브 스킬 추가
	//skillManager.AddRandomSkillToCharacter(player.get(), SkillType::PASSIVE);
	//skillManager.AddRandomSkillToCharacter(monster.get(), SkillType::PASSIVE);

	// 특정 스킬을 직접 추가
	//skillManager.AddSelectSkillToCharacter(typeid(PoisonedBlade), player.get());
	//skillManager.AddSelectSkillToCharacter(typeid(Plague), player.get());

	//UTurnSystem->BeginTurn();
	//vector<Character*> characterList{ player.get(),monster.get() };

	//// 플레이어와 몬스터의 스킬 정보 출력
	//cout << "Player Active Skills:" << endl;
	//for (const auto& skillInfo : player->skillManager->GetActiveSkillInfo())
	//{
	//	cout << skillInfo << endl;
	//}

	//cout << "Player Passive Skills:" << endl;
	//for (const auto& skillInfo : player->skillManager->GetPassiveSkillInfo())
	//{
	//	cout << skillInfo << endl;
	//}

	//auto newPlayerAttackEv = make_shared<IPlayerBattleAttackEvent>();
	//GlobalEventManager::Get().Notify(newPlayerAttackEv);

	//// 스킬 사용 테스트
	//if (!player->skillManager->UseSkill(SkillType::ACTIVE, "독이 묻은 칼"))
	//{
	//	cout << "스킬 사용 실패: 독이 묻은 칼" << endl;
	//}

	//UTurnSystem->EndTurn(characterList);
#pragma endregion


#pragma region 캐릭터 테스트 예시 코드

	//Player* player = new Player("Player");
	//Monster* monster = new Monster(1);
	//
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

	

	//while (!monster->StatManager->IsDead())
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
#pragma endregion

#pragma region 스킬 사용 예제

	//shared_ptr<Player> player = make_shared<Player>("Player");
	//player->Initialize();
	//
	//shared_ptr<Monster> monster = make_shared<Monster>();
	//monster->Initialize();
	//
	////타겟 설정합니다
	//monster->combatManager->SetTarget(player.get());
	//player->combatManager->SetTarget(monster.get());
	//
	//std::vector<Character*> battleCharacters;
	//battleCharacters.push_back(player.get());
	//battleCharacters.push_back(monster.get());
	//
	//shared_ptr<LifeStealAttack> newLifeStealAttack = make_shared<LifeStealAttack>(monster.get());
	//monster->skillManager->AddSkill(newLifeStealAttack);


	//SkillManager::GetInstance().CreateSkillFromType(typeid(Patience), player.get());
	//SkillManager::GetInstance().CreateSkillFromType(typeid(Patience), monster.get());

	//player->skillManager->AddSkill(make_shared<Unbreakable>(player.get()));

	//while (!CharacterUtility::IsDead(player.get()) && !CharacterUtility::IsDead(monster.get()))
	//{
	//	UTurnSystem->BeginTurn();

	//	player->combatManager->Attack();
	//	monster->combatManager->Attack();

	//	UTurnSystem->EndTurn(battleCharacters);
	//}

	//shared_ptr<PoisonedBlade> newPoisonedBlade= make_shared<PoisonedBlade>(monster.get());
	//monster->skillManager->AddSkill(newPoisonedBlade);
	//
	//shared_ptr<PoisonInfusion> newPoisonInfusion = make_shared<PoisonInfusion>(monster.get());
	//monster->skillManager->AddSkill(newPoisonInfusion);
	//
	//shared_ptr<PoisonFog> newPoisonFog = make_shared<PoisonFog>(monster.get());
	//monster->skillManager->AddSkill(newPoisonFog);
	//
	//shared_ptr<PoisonTrigger> newPoisonTrigger = make_shared<PoisonTrigger>(monster.get());
	//monster->skillManager->AddSkill(newPoisonTrigger);
	//
	////패시브
	//shared_ptr<Plague> newPlague = make_shared<Plague>(player.get());
	//player->skillManager->AddSkill(newPlague);
	//
	//player->combatManager->Attack();
	//auto playerAttackEvent = make_shared<IPlayerBattleAttackEvent>();
	//eventManager.Notify(playerAttackEvent);

	//monster->skillManager->UseSkill(SkillType::ACTIVE, "독이 묻은 칼");
	//monster->skillManager->UseSkill(SkillType::ACTIVE, "맹독 부여");
	//monster->skillManager->UseSkill(SkillType::ACTIVE, "독 안개");
	//monster->skillManager->UseSkill(SkillType::ACTIVE, "독 격발");

#pragma endregion
}