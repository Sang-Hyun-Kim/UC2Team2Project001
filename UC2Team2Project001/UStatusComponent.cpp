#include "pch.h"
#include "UStatusComponent.h"
#include "CharacterStatus.h"
#include <iostream>

UStatusComponent::UStatusComponent(Character* _owner)
{
    OwnerCharacter = _owner;
}

void UStatusComponent::AddState(const std::shared_ptr<ICharacterState>& NewState)
{
	// 동일한 상태 이름을 가진 상태 검색
	auto it = std::find_if(ActiveStates.begin(), ActiveStates.end(),
		[&](const std::shared_ptr<ICharacterState>& State)
		{
			return State->GetStateName() == NewState->GetStateName();
		});

	if (it != ActiveStates.end())
	{
		// 이미 존재하면 지속 시간을 더 큰 값으로 갱신
		int ExistingDuration = (*it)->GetDuration();
		int NewDuration = NewState->GetDuration();
		(*it)->SetDuration(std::max(ExistingDuration, NewDuration));

		// PoisonState의 경우, 스택을 추가로 처리
		if (auto* ExistingPoisonState = dynamic_cast<PoisonState*>(it->get()))
		{
			if (auto* NewPoisonState = dynamic_cast<PoisonState*>(NewState.get()))
			{
				ExistingPoisonState->ApplyStack(NewPoisonState->amountStack);
			}
		}
	}
	else
	{
		// 새로운 상태 추가
		ActiveStates.push_back(NewState);
	}
}

void UStatusComponent::ApplyAllEffects()
{
    // 만료되지 않은 상태들에 대해서만 Effect를 적용
    for (auto& State : ActiveStates)
    {
        if (!State->IsExpired())
        {
            State->ApplyEffect(OwnerCharacter);
        }
    }
}

void UStatusComponent::RemoveExpiredStates()
{
	ActiveStates.erase(
		std::remove_if(ActiveStates.begin(), ActiveStates.end(),
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
		ActiveStates.end()
	);
}

void UStatusComponent::DecrementAllDurations()
{
    for (auto& State : ActiveStates)
    {
        State->TickDuration();
    }
}

void UStatusComponent::PrintStates() const
{
    for (auto& State : ActiveStates)
    {
        std::cout << "[상태] " << State->GetStateName() << " (지속 시간: " << State->GetDuration() << ")\n";
    }
}

bool UStatusComponent::RemoveState(std::type_index StateType)
{
	auto it = std::find_if(ActiveStates.begin(), ActiveStates.end(),
		[&](const std::shared_ptr<ICharacterState>& State)
		{
			// typeid 결과를 std::type_index로 변환하여 비교
			return std::type_index(typeid(*State.get())) == StateType;
		});

	if (it != ActiveStates.end())
	{
		ActiveStates.erase(it);     // 상태 제거
		return true;                // 제거 성공
	}

	return false; // 해당 상태가 없으면 실패
}
