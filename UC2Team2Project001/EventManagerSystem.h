#pragma once

#include <memory>

class IEvent;

/**
 * 이벤트를 처리하는 최소 인터페이스(추상 클래스).
 * - OnEvent()는 구현 클래스에서 반드시 오버라이드해야 함.
 */
class EventManagerSystem
{
public:
    virtual ~EventManagerSystem() = default;

    // 순수 가상 함수: 파생 클래스가 구현해야 함
    virtual void OnEvent(const std::shared_ptr<IEvent>& ev) = 0;

    // 구독자 식별용 ID (GlobalEventManager에서 관리)
    int GetID() const { return ID; }
    void SetID(int newId) { ID = newId; }

private:
    int ID = -1;
};
