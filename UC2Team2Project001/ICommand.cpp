#include "pch.h"
#include "ICommand.h"
#include "Character.h"
#include "StatComponent.h"

AttackCommand::AttackCommand() : Attacker(nullptr), Defender(nullptr)
{
}

AttackCommand::AttackCommand(Character* InAttacker, Character* InDefender) : Attacker(InAttacker), Defender(InDefender)
{
	
}

void AttackCommand::Excute()
{
	if ((Attacker && Defender) && (!Attacker->StatManager->IsDead() && !Defender->StatManager->IsDead()))
	{
		Attacker->Attack(Defender);
	}
}

UseItemCommand::UseItemCommand() : User(nullptr)
{

}

UseItemCommand::UseItemCommand(Character* InUser, const string& InItemName) : User(InUser),ItemName(InItemName)
{
	
}

void UseItemCommand::Excute()
{
	if (User && !User->StatManager->IsDead())
	{
		User->UseItem(ItemName);
	}
}
