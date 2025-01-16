#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "CharacterStatus.h"
#include <typeindex>

/**

@brief 캐릭터가 보유한 각종 상태(버프/디버프 등)를 관리하는 컴포넌트*/
class UStatusComponent
{
public:
	UStatusComponent()
	{
	}

	UStatusComponent(Character* _owner);

	~UStatusComponent() = default;

	// 상태 추가 (이미 존재하는 상태이면 남은 턴을 '최대 턴'으로 갱신)
	void AddState(const std::shared_ptr<ICharacterState>& NewState);

	// 캐릭터에게 적용된 모든 상태의 효과를 적용 (매 턴마다 호출)
	void ApplyAllEffects();

	// 만료된 상태 제거
	void RemoveExpiredStates();

	// 매 턴 종료 시, 모든 상태의 지속 턴을 1씩 감소
	void DecrementAllDurations();

	// 디버그용: 상태 목록 출력
	void PrintStates() const;

	template <typename T>
	std::shared_ptr<T> GetState() const
	{
		for (const auto& State : ActiveStates)
		{
			if (auto CastedState = std::dynamic_pointer_cast<T>(State))
			{
				return CastedState;
			}
		}
		return nullptr; // 원하는 상태가 없으면 nullptr 반환
	}

	bool RemoveState(std::type_index StateType);

public:
	Character* OwnerCharacter;

	std::vector<std::shared_ptr<ICharacterState>> ActiveStates;
};
