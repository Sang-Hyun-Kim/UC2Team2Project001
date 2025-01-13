#pragma once

class Character;

class ICommand
{
public:
	ICommand() = default;
	~ICommand() = default;

	virtual void Excute() = 0; //실제 명령
};




// 여기까지가 전투 커맨드
class AttackCommand : public ICommand
{
public:
	AttackCommand();

	AttackCommand(Character* InAttacker, Character* InDefender);

	virtual void Excute() override;

private:
	Character* Attacker; //공격자
	Character* Defender; //방어자
};

class UseItemCommand : public ICommand
{
public:
	UseItemCommand();
	UseItemCommand(Character* InUser, const string& InItemName);
	virtual void Excute() override;

private:
	Character* User;
	std::string  ItemName;
};




//여기가 로비 커맨드
class ShpCommand : public ICommand
{

};

// 대화 커맨드
class TalkCommand : public ICommand
{

};

// 휴식 커맨드
class RestCommand : public ICommand
{

};