#pragma once

class Character;
class IAttackStrategy;
class IDefenseStrategy;


class CombatComponent
{
private:
	shared_ptr<Character> owner;
	shared_ptr<Character> target;
protected:
	// 공격/방어 전략
	shared_ptr<IAttackStrategy> attackStrategy;
	shared_ptr<IDefenseStrategy> defenseStrategy;

public:
	shared_ptr<Character> GetOwner()
	{
		return owner;
	}

	shared_ptr<Character> GetTarget()
	{
		return target;
	}

	void SetOwner(shared_ptr<Character> _owner);

	// 상대 설정
	void SetTarget(shared_ptr<Character> _target);

	// 공격 및 피해 처리
	virtual void Attack();
	virtual void TakeDamage(int _incomingDamage);

	// 전투 전략 설정
	void SetAttackStrategy(shared_ptr<IAttackStrategy> _newAttackStrategy);
	void SetDefenseStrategy(shared_ptr<IDefenseStrategy> _newDefenseStrategy);
};

