#pragma once

#include <memory>

class IEvent;

/**
 * 이벤트를 처리하는 기본 인터페이스.
 * - 모든 구독자는 이 인터페이스를 구현해야 합니다.
 */
class IEventManagerSystem
{
public:
    virtual ~IEventManagerSystem() = default;

    // 순수 가상 함수: 이벤트를 처리하는 메서드
    virtual void OnEvent(const std::shared_ptr<IEvent>& ev) = 0;

    // 구독자 식별용 ID (GlobalEventManager에서 관리)
    int GetID() const { return ID; }
    void SetID(int newId) { ID = newId; }

private:
    int ID = -1;
};