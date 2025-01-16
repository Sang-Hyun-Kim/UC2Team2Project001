#include "pch.h"
#include "ConsoleColorManager.h"
#include "GlobalEventManager.h"
#include "SystemContext.h"
#include "UIEventManagerSystem.h"
#include <memory>

#include "PlayerCharacter.h"
#include "Monster.h"
#include "CombatComponent.h"
#include "UTurnEventManager.h"
#include "SkillManager.h"
#include "Sanctification.h"
#include "USkillComponent.h"
#include "BasicAttack.h"
#include "PoisonedBlade.h"
#include "PoisonFog.h"



// 실행 모드를 설정합니다.
// GAME_MODE = 1 : 메인 게임 루프 실행
// GAME_MODE = 0 : 디버그 테스트 실행
#define GAME_MODE 1

// 게임 시스템 코드가 돌아갈 main 함수





int main()
{
	// 랜덤 함수 시드 설정
	srand((unsigned int)time(NULL));


	//GlobalEventManager 싱글톤 인스턴스 가져오기 
	GlobalEventManager& eventManager = GlobalEventManager::Get();

	// UI 시스템 생성  //지우지 마세요
	auto UISystem = std::make_shared<UIEventManagerSystem>();

	auto TurnEventManager = std::make_shared<UTurnEventManager>();

	eventManager.Subscribe(GSystemContext);
	eventManager.Subscribe(UISystem);
	eventManager.Subscribe(TurnEventManager);

#if GAME_MODE == 1

	while (true)
	{
		GSystemContext->Update(); // Update()로 변경해야함
	}


#elif GAME_MODE == 0
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


	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(BasicAttack), player.get());
	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(Sanctification), player.get());
	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(PoisonedBlade), player.get());
	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(PoisonFog), player.get());


	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(BasicAttack), monster.get());

	ConsoleColorManager::GetInstance().SetDefaultColor();

	TurnEventManager->BeginTurn();


	//player->combatManager->Attack();
	//monster->combatManager->Attack();

	//player->skillManager->UseSkill(SkillType::ACTIVE, "신성화");
	//player->skillManager->UseSkill(SkillType::ACTIVE, "기본 공격");
	player->skillManager->UseSkill(SkillType::ACTIVE, "독이 묻은 칼");
	player->skillManager->UseSkill(SkillType::ACTIVE, "독 안개");

	monster->skillManager->UseSkill(SkillType::ACTIVE, "기본 공격");
	
	
	TurnEventManager->EndTurn(battleCharacters);

	CharacterUtility::PrintStatus(player.get());
	CharacterUtility::PrintStatus(monster.get());

#endif // !DEBUG_TEST



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
	//

	//

	//SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(BasicAttack), player.get());
	//SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(Sanctification), player.get());
	//
	//TurnEventManager->BeginTurn();


	////player->combatManager->Attack();
	////monster->combatManager->Attack();

	////player->skillManager->UseSkill(SkillType::ACTIVE, "신성화");
	//player->skillManager->UseSkill(SkillType::ACTIVE, "기본 공격");

	//CharacterUtility::PrintStatus(player.get());
	//CharacterUtility::PrintStatus(monster.get());
	//

	//TurnEventManager->EndTurn(battleCharacters);


	//
	//
	////auto playerAttackEvent = make_shared<IPlayerBattleAttackEvent>();
	////eventManager.Notify(playerAttackEvent);
	

#pragma endregion
}