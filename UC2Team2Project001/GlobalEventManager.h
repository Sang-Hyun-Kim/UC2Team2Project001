#pragma once

#include <vector>
#include <memory>
#include "EventManagerSystem.h"

class IEvent;

class GlobalEventManager
{
private:
    GlobalEventManager();
    ~GlobalEventManager();

public:
    // 싱글톤 인스턴스 반환
    static GlobalEventManager& Get()
    {
        static GlobalEventManager instance;
        return instance;
    }

    // 복사/대입 불가
    GlobalEventManager(const GlobalEventManager&) = delete;

    GlobalEventManager& operator=(const GlobalEventManager&) = delete;

    // 구독 등록
    int Subscribe(const std::shared_ptr<IEventManagerSystem>& system);

    // 구독 해제
    void Unsubscribe(int subscriptionId);

    // 모든 구독자에게 이벤트 알림
    void Notify(const std::shared_ptr<IEvent>& ev);

private:
    int NextId = 1;

    std::vector<std::shared_ptr<IEventManagerSystem>> Listeners;
};
