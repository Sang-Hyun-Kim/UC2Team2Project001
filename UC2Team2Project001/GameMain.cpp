#include "pch.h"
#include "Character.h"
#include "IStrategy.h"
#include "GlobalEventManager.h"


// 게임 시스템 코드가 돌아갈 main 함수
int main()
{
	cout << "pch.h test" << endl;
	cout << "송정훈" << endl;
	cout << "김상현" << endl;
	cout << "남찬우" << endl;


	//코드 시작점
	srand((unsigned)time(nullptr));

	// 테스트용 캐릭터
	//Character hero("Hero", 50, 10, 5);
	//hero.SetAttackStrategy(new SimpleAttackStrategy());
	//hero.SetDefenseStrategy(new BlockDefenseStrategy());

	//Character goblin("Goblin", 30, 8, 2);
	//goblin.SetAttackStrategy(new PowerAttackStrategy());
	//goblin.SetDefenseStrategy(new EvadeDefenseStrategy());

	
}


