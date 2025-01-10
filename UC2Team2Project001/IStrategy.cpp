#include "pch.h"
#include "IStrategy.h"
#include "Character.h"

using namespace std;

void SimpleAttackStrategy::Attack(Character* Self, Character* Target) 
{
	int damage = Self->GetAttackPower();

	cout << Self->GetName() << "이(가) 간단한 공격을 수행합니다. "
		<< Target->GetName() << "은(는) 데미지 " << damage << "을(를) 받았습니다!" << endl;

	Target->TakeDamage(damage);
}

void PowerAttackStrategy::Attack(Character* Self, Character* Target) 
{
	//ToDo:랜덤 숫자가 일정하게 나오면 Seed를 도입해야 합니다.
	// 치명타 확률 30%라고 가정
	bool isCritical = (rand() % 10 < 3); 

	int baseDamage = Self->GetAttackPower();
	int damage = isCritical ? (baseDamage * 2) : baseDamage;

	if (isCritical) 
	{
		cout << Self->GetName() << "이(가) 크리티컬 파워 공격을 수행합니다! "
			<< Target->GetName() << "은(는) 데미지 " << damage << "을(를) 받았습니다!" << endl;
	}
	else 
	{
		cout << Self->GetName() << "이(가) 강력한 공격을 수행합니다. "
			<< Target->GetName() << "은(는) 데미지 " << damage << "을(를) 받았습니다!" << endl;
	}

	Target->TakeDamage(damage);
}

int BlockDefenseStrategy::CalculateDamageReceived(Character* Self, int IncomingDamage) 
{
	int finalDamage = IncomingDamage - Self->GetDefense();

	if (finalDamage < 0) finalDamage = 0;

	cout << Self->GetName() << "이(가) 방어했습니다! (" << IncomingDamage << " -> " << finalDamage << ")\n";

	return finalDamage;
}

int EvadeDefenseStrategy::CalculateDamageReceived(Character* Self, int IncomingDamage) 
{
	//ToDo:랜덤 숫자가 일정하게 나오면 Seed를 도입해야 합니다.
	// 25% 확률로 피해 0
	bool isEvaded = (rand() % 4 == 0);

	if (isEvaded) 
	{
		cout << Self->GetName() << "이(가) 공격을 완전히 회피했습니다! (0 데미지)\n";
		return 0;
	}
	else 
	{
		cout << Self->GetName() << "이(가) 회피에 실패했습니다. 데미지: " << IncomingDamage << endl;
		return IncomingDamage;
	}
}
