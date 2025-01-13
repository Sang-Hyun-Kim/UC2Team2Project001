#pragma once

class Character;

class GameState
{
public:

	//사용자 입력을 받아서 적절한 커맨드 생성 & 실행
	virtual void HanldeInput(int input) = 0;

	//처음 상태일 때 보통은 초기화하는 함수 
	virtual void Enter() {}

	//매 상태마다 실행되어야 하는 루프
	virtual void Update() {}

	//이 상태가 끝났을 때 실행되어야 하는 루프
	virtual void End() {};

	//현재 상태가 끝났는지 여부
	virtual bool IsStateEnd() { return false; }

	virtual GameState* NextState() { return nullptr; }
};

class LobbyState : public GameState
{
	LobbyState(Character* InPlayer)  : Player(InPlayer)
	{

	}

	virtual void HanldeInput(int input) override
	{
		//std::unique_ptr<ICommand> cmd;

		//switch (input)
		//{
		//case 1: //대화
		//	cmd = std::make_unique<TalkCommand>("NPC_AAA");
		//	cmd->excute();
		//	break;

		//case 2: //상점
		//	cmd = std::make_unique<ShpCommand>(
		//default:
		//	break;
		//}
	}


private:
	Character* Player;
	bool bfinished = false;
};
