#pragma once

class Character;
class IAttackStrategy;
class IDefenseStrategy;

struct  StatsData;

class UCombatComponent
{
public:
	UCombatComponent();

	UCombatComponent(Character* _owner);

	virtual void Initialize(StatsData LoadStatsData);

	// 피해 처리
	virtual void TakeDamage(int _incomingDamage);

	Character* GetOwner()
	{
		return owner;
	}

	void SetOwner(Character* _owner);

	Character* GetTarget()
	{
		return target;
	}

	// 상대 설정
	void SetTarget(Character* _target);

	// 전투 전략 설정
	void SetAttackStrategy(shared_ptr<IAttackStrategy> _newAttackStrategy);
	void SetDefenseStrategy(shared_ptr<IDefenseStrategy> _newDefenseStrategy);

	shared_ptr<IAttackStrategy> GetAttackStrategy();

private:
	Character* owner;
	Character* target;

protected:
	// 공격/방어 전략
	shared_ptr<IAttackStrategy> attackStrategy;
	shared_ptr<IDefenseStrategy> defenseStrategy;
};

