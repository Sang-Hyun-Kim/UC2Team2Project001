#pragma once

class Character;
class IAttackStrategy;
class IDefenseStrategy;


class CombatComponent
{
private:
	Character* owner;
	Character* target;
protected:
	// 공격/방어 전략
	shared_ptr<IAttackStrategy> attackStrategy;
	shared_ptr<IDefenseStrategy> defenseStrategy;

public:
	Character* GetOwner()
	{
		return owner;
	}

	Character* GetTarget()
	{
		return target;
	}

	void SetOwner(Character* _owner);

	// 상대 설정
	void SetTarget(Character* _target);

	// 공격 및 피해 처리
	virtual void Attack();
	virtual void TakeDamage(int _incomingDamage);

	// 전투 전략 설정
	void SetAttackStrategy(shared_ptr<IAttackStrategy> _newAttackStrategy);
	void SetDefenseStrategy(shared_ptr<IDefenseStrategy> _newDefenseStrategy);
};

