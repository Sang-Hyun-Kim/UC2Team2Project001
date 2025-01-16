#include "pch.h"
#include "UStatusComponent.h"
#include "CharacterStatus.h"
#include <iostream>
#include "Character.h"

UStatusComponent::UStatusComponent(Character* _owner)
{
    ownerCharacter = _owner;
}

void UStatusComponent::AddState(const std::shared_ptr<ICharacterState>& _newState)
{
	// 동일한 상태 이름을 가진 상태 검색
	auto it = std::find_if(activeStates.begin(), activeStates.end(),
		[&](const std::shared_ptr<ICharacterState>& State)
		{
			return State->GetStateName() == _newState->GetStateName();
		});

	if (it != activeStates.end())
	{
		// 이미 존재하면 지속 시간을 더 큰 값으로 갱신
		int existingDuration = (*it)->GetDuration();
		int newDuration = _newState->GetDuration();
		(*it)->SetDuration(std::max(existingDuration, newDuration));

		// PoisonState의 경우, 스택을 추가로 처리
		if (auto* existingPoisonState = dynamic_cast<PoisonState*>(it->get()))
		{
			if (auto* newPoisonState = dynamic_cast<PoisonState*>(_newState.get()))
			{
				existingPoisonState->ApplyStack(newPoisonState->amountStack);
			}
		}
	}
	else
	{
		// 새로운 상태 추가
		activeStates.push_back(_newState);
	}
}

void UStatusComponent::ApplyAllEffects()
{
    // 만료되지 않은 상태들에 대해서만 Effect를 적용
    for (auto& state : activeStates)
    {
        if (!state->IsExpired())
        {
            state->ApplyEffect(ownerCharacter);
        }
    }
}

void UStatusComponent::RemoveExpiredStates()
{
	activeStates.erase(
		std::remove_if(activeStates.begin(), activeStates.end(),
			[](const std::shared_ptr<ICharacterState>& _state)
			{
				if (_state->IsExpired())
				{
					_state->EffectBeforeRemove();

					cout << _state->GetStateName() << " 상태가 해제되었습니다." << endl;
					return true;
				}
				return false;
			}
		),
		activeStates.end()
	);
}

void UStatusComponent::DecrementAllDurations()
{
    for (auto& state : activeStates)
    {
        state->TickDuration();
    }
}

void UStatusComponent::PrintStates() const
{
    for (auto& state : activeStates)
    {
        std::cout << "[상태] " << state->GetStateName() << " (지속 시간: " << state->GetDuration() << ")\n";
    }
}

bool UStatusComponent::RemoveState(std::type_index _stateType)
{
	auto it = std::find_if(activeStates.begin(), activeStates.end(),
		[&](const std::shared_ptr<ICharacterState>& state)
		{
			// typeid 결과를 std::type_index로 변환하여 비교
			return std::type_index(typeid(*state.get())) == _stateType;
		});

	if (it != activeStates.end())
	{
		activeStates.erase(it);     // 상태 제거
		return true;                // 제거 성공
	}

	return false; // 해당 상태가 없으면 실패
}
