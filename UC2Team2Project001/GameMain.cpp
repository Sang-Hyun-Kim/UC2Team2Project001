#include "pch.h"
#include "GameSystem.h"

// 게임 시스템 코드가 돌아갈 main 함수

int main()
{

	GSystemContext->currentSystem = GLobbySystem;


	while (true)
	{
		GSystemContext->currentSystem->EnterSystem();
	}

	//GLobbySystem->CreatePlayer();
	//GLobbySystem->PlayerMove();
	//GBattleSystem->EnterSystem();


}
