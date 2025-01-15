#include "pch.h"
#include "UStatusComponent.h"
#include "CharacterStatus.h"
#include <iostream>

void UStatusComponent::AddState(const std::shared_ptr<ICharacterState>& NewState)
{
	// 이미 동일한 이름의 상태가 있는지 확인
	auto it = std::find_if(ActiveStates.begin(), ActiveStates.end(),
		[&](const std::shared_ptr<ICharacterState>& State)
		{
			return State->GetStateName() == NewState->GetStateName();
		}
	);

	// 존재하면 '남은 턴'을 더 큰 값으로 갱신
	if (it != ActiveStates.end())
	{
		int ExistingDuration = (*it)->GetDuration();
		int NewDuration = NewState->GetDuration();
		(*it)->SetDuration(std::max(ExistingDuration, NewDuration));
	}
	else
	{
		// 존재하지 않으면 새 상태 추가
		ActiveStates.push_back(NewState);
	}
}

void UStatusComponent::ApplyAllEffects(Character* Target)
{
	// 만료되지 않은 상태들에 대해서만 Effect를 적용
	for (auto& State : ActiveStates)
	{
		if (!State->IsExpired())
		{
			State->ApplyEffect(Target);
		}
	}
}

void UStatusComponent::RemoveExpiredStates()
{
	ActiveStates.erase(
		std::remove_if(ActiveStates.begin(), ActiveStates.end(),
			[](const std::shared_ptr<ICharacterState>& State)
			{
				return State->IsExpired();
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
