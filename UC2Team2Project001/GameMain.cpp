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
// 게임 시스템 코드가 돌아갈 main 함수

using namespace std;

int main()
{
	// 랜덤 함수 시드 설정
	srand(time(NULL));
	

	// GlobalEventManager 싱글톤 인스턴스 가져오기 //지우지마세요
	GlobalEventManager& eventManager = GlobalEventManager::Get();

	//// UI 시스템 생성  //지우지 마세요
	auto UISystem = std::make_shared<UIEventManagerSystem>();
	eventManager.Subscribe(UISystem);

	//GSystemContext->currentSystem = GLobbySystem;


	//while (true)
	//{
	//	GSystemContext->currentSystem->Update(); // Update()로 변경해야함
	//}


#pragma region 스킬 사용 예제

	//shared_ptr<Player> player = make_shared<Player>("Player");
	//shared_ptr<Monster> monster = make_shared<Monster>(CharacterUtility::GetStat(player.get(), StatType::Level));
	//monster->combatManager->SetTarget(player);
	//monster->skillManager->UseSkill(SkillType::ACTIVE, "기본 스킬");

#pragma endregion
}