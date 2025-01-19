# 팀명: Auto
---
## 프로젝트 명: 뒷 동네 마왕 잡으러 가기
## 프로젝트 개요
  - 프로젝트 작업 기간: 2025/01/10 ~ 2025/01/16
  - C++ 디자인 패턴을 적용한 객체 지향 방식 TEXT RPG 게임을 만들고 싶었습니다. 저희가 구현하고자 하는 기능 과 시스템이 코드 재사용, 확장성, 유지 보수성을 가지려면 어떻게 구현해야하는지 기획, 설계 한 뒤 이를 구현하는 과정을 가졌습니다.
  - 옵저버 패턴, 싱글톤 패턴, 팩토리 패턴, 추상 클래스 패턴, 상태 패턴, 커맨드 패턴 등을 응용해서 설계한 기능을 구현하고자 했습니다.  
## 주요 기능 요약
  - 로비, 전투, 상점을 기능하는 GameSystem 서브 클래스들을 제작했고, 모든 System을 괸리하는 SystemContext가 Update 함수를 통해 어느 GameSystem 이든 실행하고 플레이어가 방을 이동하는 방식으로 구현하였으며, 각 System 안에는 저장된 SystemState 별로 원하는 타이밍에 의도한 기능을 호출하도록 하였습니다.
  - 플레이어가 수동 전투를 진행하며 스킬과 아이템을 자유롭게 사용하며, 현재 자신의 스탯 정보를 확인합니다.
  - 플레이어에게 턴 시스템을 부여하여 스킬과 아이템이 적용하는 효과가 Turn이라는 Duration을 가지도록 설계 및 구현 하였고, 사용한 스킬은 일정 Turn 사용할 수 없는 CoolDown 시스템을 적용하였습니다.
  - 모든 아이템과 스킬을 관리하는 Singleton 인스턴스를 통해 게임 시작시 플레이어에게 Skill을 부여할 때, 전투에서 승리하고 플레이어가  
 ### 사용한 라이브러리
 --- 
  - windows.h
  - iostream
  - vector
  - random
  - unordered_map
  - memory
  - sstream
  - limits
  - string
  - ctype.h
  - cctype
  - algorithm
  - functional
  - typeindex
  - regex
  - chrono
  - thread
  - iomanip  // std::setw, std::setprecision
 ---
## 개발 환경
  ---
  - IDE: Visual Studio 2022
  - Language : C++
  - Compiler : MSVC C++ 17
  - others: Git Desktop

### 기능설명
  - 전체 시스템 플로우 차트
![Image](https://github.com/user-attachments/assets/a08c011c-f997-4643-b899-b0e1a9d912bb)
  - UML: https://lucid.app/lucidchart/b9180622-3661-4862-aa7a-6da03484a47f/edit?invitationId=inv_5c977377-3e9a-475c-99cc-0a27c18cc749&page=Qq6J2hiGBQnQ#
    
# 주요 기능 설명

## 목차

# 목차

1. [Event System](#event-systen)
   - [개요](#개요)
   - [주요 클래스](#주요-클래스)
   - [사용 예시](#사용-예시)
2. [Game 시스템](#game-시스템)
   - [개요](#개요-1)
   - [주요 클래스](#주요-클래스-1)
     - [SystemContext](#systemcontext)
     - [LobbySystem](#lobbysystem)
     - [LobbySystemState](#lobbysystemstate)
     - [BattleSystem](#battlesystem)
     - [BattleSystemState](#battlesystemstate)
     - [ShopSystem](#shopsystem)
   - [사용 예시](#사용-예시-1)
3. [캐릭터 시스템](#캐릭터-시스템)
   - [개요](#개요-2)
   - [주요 클래스](#주요-클래스-2)
   - [사용 예시](#사용-예시-2)
4. [스킬 시스템](#스킬-시스템)
   - [개요](#개요-3)
   - [주요 클래스](#주요-클래스-3)
   - [사용 예시](#사용-예시-3)
5. [인풋 시스템](#인풋-시스템)
   - [개요](#개요-4)
   - [주요 클래스](#주요-클래스-4)
   - [사용 예시](#사용-예시-4)
6. [아이템 시스템](#아이템-시스템)
   - [개요](#개요-5)
   - [주요 클래스](#주요-클래스-5)
   - [사용 예시](#사용-예시-5)

## Event System

이 프로젝트의 이벤트 시스템은 다양한 게임 이벤트를 효율적으로 관리하고 처리할 수 있도록 설계되었습니다. 아래는 시스템의 주요 구성 요소와 사용법에 대한 설명입니다.

## 코드 구조

```
📂 Project
├── 📂 Events
│   ├── IEvent.h  
│   ├── IEventTypes.h
│   ├── CharacterEventTypes.h
│   ├── ItemEventTypes.h
│   └── CombatEventTypes.h
├── 📂 Managers
│   ├── GlobalEventManager.h
│   ├── GlobalEventManager.cpp
│   ├── IEventManagerSystem.h
│   └── UIEventManagerSystem.h
└── main.cpp
```
![image](https://github.com/user-attachments/assets/d3bf07af-6427-4a3a-889d-f0f9ddefa5a3)

---

## 주요 클래스 및 구성 요소

### 1. `IEvent`
모든 이벤트의 공통 부모 클래스입니다. 모든 이벤트는 `IEvent`를 상속받아 정의됩니다.

```cpp
class IEvent {
public:
    virtual ~IEvent() = default;
};
```

### 2. `IEventManagerSystem`
이벤트를 처리하고 구독을 관리하는 인터페이스입니다.

- **주요 메서드**
  - `OnEvent`: 전달받은 이벤트를 처리합니다.
  - `Subscribe`: 특정 이벤트 타입에 대한 핸들러를 등록합니다.
  - `Publish`: 등록된 모든 핸들러에 이벤트를 전달합니다.

```cpp
class IEventManagerSystem {
public:
    virtual ~IEventManagerSystem() = default;

    virtual void OnEvent(std::shared_ptr<IEvent> _event) = 0;

    template<typename T>
    int Subscribe(std::function<void(T*)> _handler);

    void Publish(std::shared_ptr<IEvent> _event);
};
```

### 3. `GlobalEventManager`
전역에서 이벤트 시스템을 관리하는 싱글톤 클래스입니다. 구독, 구독 해제, 이벤트 알림 등의 작업을 수행합니다.

- **주요 메서드**
  - `Subscribe`: 새로운 구독자를 등록합니다.
  - `Unsubscribe`: 구독을 해제합니다.
  - `Notify`: 모든 구독자에게 이벤트를 전달합니다.

```cpp
class GlobalEventManager {
public:
    static GlobalEventManager& Get();

    int Subscribe(const std::shared_ptr<IEventManagerSystem>& _system);
    void Unsubscribe(int _subscriptionId);
    void Notify(std::shared_ptr<IEvent> _callEv);
};
```

### 4. 이벤트 예제: `ICharacterDamagedEvent`
캐릭터가 데미지를 받는 이벤트입니다.

```cpp
class ICharacterDamagedEvent : public IEvent {
public:
    std::string characterName;
    int damage;
    int hp;

    ICharacterDamagedEvent(const std::string& _name, int _dmg, int _hp)
        : characterName(_name), damage(_dmg), hp(_hp) {}
};
```

---

## 사용법

### 1. 이벤트 구독
특정 이벤트를 처리하기 위해 이벤트 핸들러를 등록합니다.

```cpp
std::shared_ptr<IEventManagerSystem> eventSystem = std::make_shared<UIEventManagerSystem>();
GlobalEventManager::Get().Subscribe(eventSystem);

eventSystem->Subscribe<ICharacterDamagedEvent>([](ICharacterDamagedEvent* e) {
    std::cout << e->characterName << " received " << e->damage << " damage.\n";
});
```

### 2. 이벤트 발행
이벤트를 생성하고 발행하여 모든 구독자가 처리할 수 있도록 합니다.

```cpp
std::shared_ptr<ICharacterDamagedEvent> damageEvent = std::make_shared<ICharacterDamagedEvent>("Hero", 50, 450);
GlobalEventManager::Get().Notify(damageEvent);
```

### 3. 이벤트 처리
등록된 핸들러는 발행된 이벤트를 자동으로 처리합니다.

```cpp
void UIEventManagerSystem::OnEvent(std::shared_ptr<IEvent> ev) {
    Publish(ev);
}
```

---



---

## 주요 특징

1. **유연한 이벤트 구독 및 발행**
   - 특정 이벤트 타입에 대한 구독과 핸들러 등록이 가능하며, 타입 안전성을 보장합니다.

2. **모듈화된 설계**
   - 이벤트 및 이벤트 관리자는 독립적으로 설계되어 코드의 재사용성과 유지보수성이 높습니다.

3. **실시간 이벤트 처리**
   - 이벤트 발행 시, 등록된 모든 핸들러가 호출되어 즉각적으로 처리됩니다.

---

## 향후 개선 사항

- 이벤트 처리의 성능 최적화를 위해 비동기 처리 기능 추가
- 이벤트 로그 시스템 구현
- 이벤트 간 의존성 관리 및 우선순위 처리 기능 추가
- 현재 시스템에서는 다수의 게임 로직이 이벤트와 강하게 연결되어 있어, 에러 발생 시 디버깅 과정에서 호출 위치와 방법을 추적하는 데 어려움이 있습니다.

---

## 캐릭터 시스템 

- 캐릭터 시스템은 플레이어, 몬스터, 보스 등 다양한 캐릭터 타입을 관리하기 위해 설계된 모듈입니다. 이 시스템은 스탯, 스킬, 전투 메커니즘 및 보상 관리를 모듈식으로 처리하며, 확장성과 유지보수성을 염두에 두고 설계되었습니다.

---
##클래스 다이어그램

![image](https://github.com/user-attachments/assets/bb0d8961-b49d-4493-861a-71fed4931fb9)

![image](https://github.com/user-attachments/assets/ae78ced7-0324-4824-b3f6-e495b9a9f84e)


### 주요 기능

### 모듈형 디자인
- **스탯 관리**: `UStatsComponent`를 통해 HP, MP, 공격력 등 캐릭터의 스탯을 중앙에서 관리.
- **전투 시스템**: 공격 및 방어 전략을 포함하여 다양한 게임 플레이 메커니즘 제공.
- **스킬 통합**: `USkillComponent`를 통해 각 캐릭터에 고유한 스킬 추가 가능.
- **보상 시스템**: 몬스터 처치 시 보상 생성, 캐릭터 타입별로 맞춤 설정 가능.

### JSON 통합
- **데이터 기반 디자인**: JSON 파일에서 스탯과 보상을 로드 및 저장하여 코드 수정 없이 캐릭터 구성 업데이트 가능.

### 확장성
- 새로운 캐릭터 타입, 전략 또는 컴포넌트를 쉽게 통합 가능.

---

### 핵심 클래스 및 컴포넌트

### 1. Character (기본 클래스)
`Character` 클래스는 모든 엔티티의 기본이 되는 클래스입니다. 공통 속성과 메서드를 정의하며, 다음 기능을 제공합니다:

- **초기화**: 스탯, 전투, 스킬, 상태 컴포넌트 설정.
- **보상 생성**: 사망 시 보상을 생성하는 로직.
- **정보 표시**: 스탯 및 캐릭터 정보를 출력.

#### 주요 멤버
- `displayName`: 게임에 표시되는 이름. 예를 들어, JSON 파일에서 불러온 캐릭터의 이름이 "Slime"이라면, `displayName`은 화면에 "슬라임"으로 표시됩니다.
- `statManager`: 스탯 관리 (HP, MP, 공격력 등).
- `combatManager`: 전투 로직 관리.
- `skillManager`: 캐릭터 스킬 관리.
- `statusManager`: 상태 효과 관리.

---

### 2. Player (파생 클래스)
`Player` 클래스는 `Character`를 상속받아 플레이어 캐릭터의 고유 기능을 추가로 제공합니다.

#### 주요 기능
- **인벤토리 관리**: `Inventory`와 통합하여 아이템 관리.
- **아이템 사용**: 플레이어나 다른 캐릭터를 대상으로 아이템 사용 가능.

---

### 3. Monster (파생 클래스)
`Monster` 클래스는 플레이어가 아닌 캐릭터를 나타내며, 동적으로 스탯을 조정하고 보스를 설정하는 기능이 추가되었습니다.

#### 주요 기능
- **동적 스탯 조정**: 플레이어 레벨에 따라 스탯 자동 조정.
- **보스 식별**: 특정 몬스터는 보스로 설정되어 더 큰 도전과 보상을 제공.

---

### 4. UStatsComponent
모든 캐릭터의 스탯을 관리하며, 초기화, 변경 및 경계값 제한을 처리합니다.

#### 주요 기능
- **동적 스탯 조정**: HP, MP, 공격력 등의 스탯을 동적으로 수정.
- **경험치 및 레벨 업**: 경험치 증가를 처리하고 레벨 업 이벤트를 처리.
- **사망 처리**: 캐릭터가 사망했을 때 적절한 이벤트를 트리거.

---

### 5. UCombatComponent
캐릭터 간 전투 상호작용을 관리하며, 공격 및 방어 전략을 처리합니다.

#### 주요 기능
- **공격 전략**: `BasicAttackStrategy`와 같은 다양한 공격 방식 제공.
- **방어 전략**: `BlockDefenseStrategy`와 같은 다양한 방어 방식 제공.
- **피해 계산**: 방어 전략을 적용하여 최종 피해 결정.

---

### 6. StatsLoader
JSON 통합을 담당하며, 스탯과 보상을 로드 및 저장합니다.

#### 주요 기능
- **스탯 로드**: JSON 파일에서 캐릭터의 스탯 데이터를 로드.
- **보상 로드**: 몬스터의 특정 보상을 로드.
- **스탯 저장**: 수정된 스탯을 JSON 파일에 저장.

---

## 사용 예시

1. **캐릭터 초기화**:
   - `Player`와 `Monster` 인스턴스가 `Initialize()`를 호출하여 컴포넌트 설정 및 JSON에서 스탯을 로드.
   - JSON 형식 오류가 발생할 수 있으며, 이를 방지하려면 JSON 파일이 올바른 구조를 가지고 있는지 사전에 검증하는 절차가 필요합니다. 오류가 발생하면 디버깅 메시지를 출력하여 문제를 파악하고 수정할 수 있습니다.
2. **전투 상호작용**:
   - 캐릭터는 공격 및 방어 전략을 활용하여 전투 수행.
   - 스탯 및 전략에 따라 동적으로 피해 계산.
3. **보상**:
   - 몬스터를 처치하면 골드, 경험치, 아이템 등의 보상이 생성.

---

## JSON 구조

모든 캐릭터의 스탯과 보상은 간단하고 사람이 읽기 쉬운 JSON 형식으로 저장됩니다. 예제:

```json
{
  "Characters": {
    "Player": {
      "Stats": {
        "HP": 100,
        "MaxHP": 100,
        "MP": 50,
        "MaxMP": 50,
        "AttackPower": 10,
        "Defense": 5,
        "CriticalChance": 0.05,
        "EvasionRate": 0.0,
        "Level": 1,
        "Experience": 0,
        "MaxExperience": 100
      },
      "AttackStrategy": {
        "Type": "BasicAttack"
      },
      "DefenseStrategy": {
        "Type": "BlockDefense"
      }
    },
    "Slime": {
      "Stats": {
        "HP": 20,
        "MaxHP": 20,
        "AttackPower": 5,
        "Defense": 1
      },
      "Rewards": {
        "Experience": 200,
        "Gold": 50
      }
    }
  }
}
```

---

## 시스템 확장 방법

1. **새로운 캐릭터 타입 추가**:
   - `Character`를 상속받는 새로운 클래스를 정의하고 필요한 메서드를 오버라이드.
2. **맞춤 전략 구현**:
   - `IAttackStrategy` 또는 `IDefenseStrategy`를 구현하는 새로운 클래스를 생성.
3. **JSON 업데이트**:
   - 새로운 캐릭터에 대한 스탯과 보상을 JSON 파일에 정의.

[[목차로 돌아가기]](#목차)

---
## 스킬 시스템 문서

## 개요
이 프로젝트의 **스킬 시스템**은 캐릭터의 스킬을 관리하기 위한 강력하고 확장 가능한 프레임워크를 제공합니다. 액티브 스킬과 패시브 스킬, 스킬 조건, 효과, 행동을 지원하며, 모듈성과 재사용성을 극대화하여 다른 부분에 영향을 주지 않고도 스킬을 추가, 수정, 삭제할 수 있습니다.

## 목표

이 스킬 시스템은 강력하고 유연하게 설계되어, 다양한 기획 의도에 맞춰 스킬을 손쉽게 생성하고 구현할 수 있습니다. 

---

## 주요 구성 요소

### 1. **스킬 클래스 계층 구조**
스킬 시스템의 핵심 클래스는 다음과 같이 구성됩니다:
- **Skill**: 모든 스킬의 기본 클래스.
  - **ActiveSkill**: 캐릭터가 능동적으로 사용하는 스킬.
  - **PassiveSkill**: 특정 이벤트가 발생했을 때 자동으로 발동되는 스킬.
 
![image](https://github.com/user-attachments/assets/9f95f6a4-675f-444a-abc4-5d19fc956370)


#### 스킬 데이터 구조
스킬은 `FSkillData` 구조체로 표현됩니다:
```cpp
struct FSkillData {
    std::string skillName;          // 스킬 이름
    std::string skillDescription;   // 스킬 설명
    int mpCost;                     // 마나 비용
    int maxCooldown;                // 최대 쿨타임(턴)
    int currentCooldown;            // 현재 쿨타임
    Character* owner;               // 스킬 소유자
    std::shared_ptr<ISkillAction> action;        // 스킬이 수행하는 액션
    std::vector<std::shared_ptr<ISkillEffect>> effects; // 스킬의 효과들
    std::vector<std::shared_ptr<ISkillCondition>> conditions; // 스킬 조건
};
```

---

### 2. **스킬 조건**
스킬 조건은 스킬 사용 가능 여부를 결정합니다. 구현된 조건은 다음과 같습니다:
- **ManaCondition**: 캐릭터가 충분한 마나를 가지고 있는지 확인.
- **CooldownCondition**: 스킬이 쿨타임 상태가 아닌지 확인.
- **AliveCondition**: 대상이 살아 있는지 확인.
- **StunCondition**: 소유자가 기절 상태가 아닌지 확인.

각 조건은 `ISkillCondition` 인터페이스를 구현합니다:
```cpp
class ISkillCondition {
public:
    virtual ~ISkillCondition() = default;
    virtual bool Check(Skill* checkSkill) = 0; // 조건 확인
    virtual void CannotUseSkill() = 0;        // 조건 실패 시 호출
};
```
![image](https://github.com/user-attachments/assets/fd6bbdf4-580c-4ec7-bd20-0663386967e3)


---

### 3. **스킬 액션**
액션은 스킬이 사용될 때 실행되는 동작을 정의합니다. 예시:
- **NormalAttackAction**: 일반 공격 실행.
- **AttackAction**: 지정된 피해량을 가함.
- **PoisonTriggerAction**: 대상의 독 스택을 폭발시킴.
- **GlacialShardAction**: 피해를 입히고 방어력을 감소시킴.

각 액션은 `ISkillAction` 인터페이스를 구현합니다:
```cpp
class ISkillAction {
public:
    virtual ~ISkillAction() = default;
    virtual void ExecuteAction() = 0; // 액션 실행
};
```

![image](https://github.com/user-attachments/assets/7f2c9551-811c-44df-a054-0978c92e7db9)



---

### 4. **스킬 효과**
효과는 스킬 사용 시 추가적으로 발생하는 결과를 나타냅니다. 예시:
- **IBuffEffect**: 버프 또는 디버프 적용.
- **IPoisonEffect**: 독 스택 추가.
- **IHealingEffect**: 체력 회복.
- **IUnbreakableEffect**: 일시적인 무적 상태 부여.

각 효과는 `ISkillEffect` 인터페이스를 구현합니다:
```cpp
class ISkillEffect {
public:
    virtual ~ISkillEffect() = default;
    virtual void PreEffect() = 0;  // 메인 액션 실행 전 실행
    virtual void PostEffect() = 0; // 메인 액션 실행 후 실행
};
```


![image](https://github.com/user-attachments/assets/2022ea98-db54-4d9e-8749-b9a0def00bba)


---

### 5. **스킬 매니저**
`SkillManager`는 싱글톤 클래스로 다음과 같은 역할을 수행합니다:
- 스킬 등록 및 생성.
- 캐릭터에게 스킬 할당.
- 고유하거나 랜덤한 스킬 할당 보장.

#### 스킬 등록
스킬은 팩토리 패턴을 사용해 등록됩니다:
```cpp
void RegisterSkill() {
    skillFactory[typeid(T)] = [](Character* owner) -> std::shared_ptr<Skill> {
        return std::make_shared<T>(owner);
    };
}
```

#### 사용 예시
```cpp
SkillManager::GetInstance().RegisterSkill<PoisonInfusion>();
SkillManager::GetInstance().AddRandomSkillToCharacter(playerCharacter, SkillType::ACTIVE);
```

---

### 6. **스킬 컴포넌트**
각 캐릭터는 `USkillComponent`를 가지며:
- 액티브 스킬과 패시브 스킬을 저장.
- 스킬 사용 및 쿨타임 관리.
- 이벤트를 통해 패시브 스킬 트리거 처리.

#### 스킬 사용
```cpp
bool USkillComponent::UseSkill(const std::string& skillName, SkillType skillType) {
    auto skillList = ChooseSkillList(skillType);
    if (skillList.count(skillName)) {
        return skillList[skillName]->UseSkill();
    }
    return false;
}
```

---

## 스킬 예시

### 액티브 스킬: Poison Infusion
대상의 독 스택을 두 배로 증가시킵니다.
```cpp
PoisonInfusion::PoisonInfusion(Character* owner) : ActiveSkill(owner) {
    skillData = FSkillData(owner, "Poison Infusion", "대상의 독 스택을 두 배로 증가시킵니다.", 0, 2);
    skillData.action = std::make_shared<PoisonIntensifierAction>();
    skillData.conditions = { std::make_shared<CooldownCondition>(), std::make_shared<AliveCondition>() };
    SkillInit(this);
}
```

### 패시브 스킬: Mana Mastery
받은 피해량의 10%만큼 마나를 회복합니다.
```cpp
ManaMastery::ManaMastery(Character* owner) : PassiveSkill(owner) {
    skillData = FSkillData(owner, "Mana Mastery", "받은 피해량의 10%만큼 마나를 회복합니다.", 0, 0);
    handlers.insert(typeid(ICharacterDamagedEvent));
    SkillInit(this);
}
```

---

## 주요 특징
1. **모듈화 설계**: 각 스킬, 액션, 효과가 독립적으로 구현됨.
2. **확장성**: 새로운 스킬과 효과를 최소한의 코드 변경으로 추가 가능.
3. **이벤트 기반 트리거**: 패시브 스킬이 이벤트 핸들러를 통해 발동.
4. **재사용성**: 조건 및 효과 등 공유 가능한 구성 요소로 중복 감소.

---

## 새로운 스킬 추가 방법
1. **스킬 정의**: `ActiveSkill` 또는 `PassiveSkill`에서 파생된 새 클래스 구현.
2. **스킬 데이터 설정**: 이름, 설명, 비용, 기타 속성을 생성자에서 설정.
3. **조건 및 효과 추가**: 스킬 사용 조건과 효과 정의.
4. **스킬 등록**: `SkillManager`에 추가.
```cpp
SkillManager::GetInstance().RegisterSkill<NewSkill>();
```
5. **스킬 할당**: `AddSkill` 또는 `AddRandomSkillToCharacter`를 사용해 캐릭터에 할당.

[[목차로 돌아가기]](#목차)


---


## 상태 시스템 문서

## 개요
**상태 시스템**은 캐릭터의 상태를 관리하기 위한 확장 가능한 프레임워크를 제공합니다.
각 상태는 모듈성과 재사용성을 극대화하여 다른 부분에 영향을 주지 않고도 상태를 추가, 수정, 삭제할 수 있습니다.

## 목표

상태 시스템은 손쉽게 생성하고 구현해서 원하는 스킬 효과에 넣어서 사용 가능합니다.

---

## 주요 구성 요소

### 1. **상태 클래스 계층 구조**
상태 시스템의 핵심 클래스는 다음과 같이 구성됩니다.
- **UStatusComponent**: 캐릭터에 대해 상태 추가 및 제거 등 상태를 관리하는 클래스
 - **ICharacterStatus**: 모든 상태의 기본 인터페이스

	- 상태 효과 적용(대미지, 버프, 디버프 등)
	- 매 턴마다 지속 시간 감소
	- 상태가 만료되었는지 확인
	- 상태가 제거되기 전에 호출 (스탯 복구 로직 등)
	- 상태 이름 반환
	- 지속 시간 반환
	- 지속 시간 설정
	- 상태 스택 추가
	- 상태 이름
	- 상태 지속 시간
	- 상태 스택

```cpp

class ICharacterState
{
public:
	ICharacterState(const string& _inStateName, int _inDuration) : stateName(_inStateName), duration(_inDuration);
	virtual ~ICharacterState();
	virtual void ApplyEffect(Character* _target) = 0;
	virtual void TickDuration();
	virtual bool IsExpired() const;
	virtual void EffectBeforeRemove();
	virtual const std::string& GetStateName() const;
	virtual int GetDuration() const;
	virtual void SetDuration(int _newDuration);
	virtual void ApplyStack(int _newStack);
protected:
	string stateName;
	int duration;
public:
	int currentStack = 1;
};

```

### 상태 구조
상태는 이름, 지속시간, 스택을 기본으로 각 하위 클래스에서 상태 효과를 구현 합니다.

---

### 2. **상태 발생 흐름**
상태는 스킬 내부 효과 발생 부분에서 대상 캐릭터에 적용되고 상태에 따라 즉시 혹은 턴이 끝나는 시점 등 다양한 시기에 효과가 발생 합니다.

### 스킬 사용 -> 스킬 액션 이전 효과 발생(**상태 효과 부여 가능**) -> 스킬 액션  발생
### 	      -> 스킬 액션 이후 효과 발생(**상태효과 부여 가능**)

---

### 3. **구현된 상태 효과**
- **BurnState**: 화상 상태 => 지속 시간 동안 일정한 화상 피해를 입힘.

- **ModifyDefenseState**: 방어력 증감 상태 => 지속 시간 동안 방어력이 증가 하거나 감소.

- **StunState**: 기절 상태 => 지속 시간 동안 기절이 걸려서 행동이 불가함.

- **PoisonState**: 중독 상태 => 지속 시간 동안 **중첩된 스택**에 비례한 독 피해를 입힘.

- **UnbreakableState**: 불굴 상태 => 죽음에 이르는 피해를 입었을 경우 지속 시간 동안 체력을 1로 고정하고 지속 시간 내로 적을 처치시 체력을 20회복하고 불굴 상태를 해제. 지속 시간 내로 적을 처치하지 못했을 경우 불굴 상태를 해제하고 사망.

- **ModifyStatState**: 스탯 수정 상태 => 지속 시간 동안 스탯이 증가 하거나 감소.

- **CursedSealState**: 저주 상태 => 지속 시간 동안 일정한 피해를 입힘.

- **SanctificationState**: 신성화 상태 => 지속 시간 동안 시전자는 공격력, 방어력, 회피력이 증가, 적은 각 스탯 감소.

- **RageState**: 분노 상태 => 한 턴 아무 것도 하지 않고, 다음 한 턴 기본 공격에 공격력의 500% 피해를 입힘.

## 스킬 효과에 상태 적용 예시

### IPoisionEffect : 중독 효과
중독 상태를 부여.
- AddState로 상태이상을 추가하고 ApplyState로 상태이상 적용
```cpp

void IPoisonEffect::PostEffect()
{
	Character* target = parentSkill->GetTarget();

	target->statusManager->AddState(make_shared<PoisonState>(2, 5, amountStack));
}

```

---


## 아이템 시스템 문서 


## Item  
- 모든 아이템들이 공통으로 상속하는 클래스입니다.
- 이 클래스를 상속해서 다양한 아이템을 정의할 수 있습니다.

### 구조 
- **itemNumber** : 아이템 고유 번호.
- **name** : 아이템 이름
- **description** : 아이템 설명
- **value** :  아이템 가치

### 주요 기능 
**use** :  순수 가상 함수로 캐릭터를 대상으로 아이템을 사용하는 메서드

#### <예시 코드>
```cpp
    Character player("Hero", 100);
    shared_ptr<Item> potion = make_shared<HealthPotion>();
    potion->use(&player);
```

**clone** : 프로토타입 패턴을 활용하여 아이템을 복제하는 함수로 아이템 매니저에 저장된 아이템을 반환할때 사용한다.

#### <예시 코드>
```cpp

    //아이템 매니저에서 인스턴스를 가지고옴
    ItemManager& itemManager = ItemManager::GetInstance();

    // 인스턴스에 있는 아이템 가져와서 복제
    shared_ptr<Item> clonedItem = itemManager.getItem(0)->clone();

```

**getInfoTextForShop** : 상점에서 사용하는 아이템 정보 반환

#### <예시 코드>
```cpp

    // HealthPotion 객체 생성
    shared_ptr<Item> potion = make_shared<HealthPotion>();

    // 상점 정보를 출력
    cout << potion->getInfoTextForShop() << endl;

```


## ItemManager  
- 게임 내에서 관리되는 모든 아이템을 한 곳에서 관리하는 싱글턴 패턴 기반의 클래스 입니다.

### 구조
- **items** : unordered_map 을 사용해 고유한 키 값으로 아이템을 저장
- **nextKey** : 아이템을 저장할 때 사용되는 다음 키 값.

### 주요 기능
**GetInstance** : 싱글턴으로 만들어진 아이템 매니저 인스턴스를 가져옵니다.

#### <예시 코드>
```cpp

ItemManager::GetInstance();

```

**getRandomItem** : 아이템 매니저에 저장된 랜덤한 아이템 하나를 반환

#### <예시 코드>
```cpp

ItemManager::GetInstance()-> getRandomItem();

```

## Inventory 
- 플레이어가 소유한 아이템과 골드를 관리하는 클래스 입니다.
- 이 클래스는 플레이어 클래스에서 생성됩니다.

### 구조 
- **addItem** , **removeItem** : 아이템 저장, 삭제

#### <예시 코드>
```cpp

    // 플레이어 객체 생성
    Player player("Hero");

    // HealthPotion 아이템 추가
    player.inventoryComponent->addItem(make_shared<HealthPotion>());
    player.inventoryComponent->addItem(make_shared<HealthPotion>());

```

- **useItem** : 아이템을 특정 캐릭터를 대상으로 사용 가능.

#### <예시 코드>
```cpp

    // 플레이어 객체 생성
    Player player("Hero");
    player.UseItem(0, &player);

```

- **IsEmpty**: 인벤토리가 비어 있는지 확인.

#### <예시 코드>
```cpp

    // 플레이어 객체 생성
    Player player("Hero");
    player.inventoryComponent.IsEmpty();

```

- **addGold**, **removeGold** : 골드 추가 및 삭제.

#### <예시 코드>
```cpp
    
    Player player("Hero");

    // 골드 추가
    player.inventoryComponent.addGold(100); // 100 골드 추가

    // 골드 소모
    player.inventoryComponent.removeGold(50); // 50 골드 소모

```

- **displayInventory** : 현재 저장된 아이템과 골드 정보를 출력.

#### <예시 코드>
```cpp
    
    // 플레이어 객체 생성
    Player player("Hero");
    
    // 인벤토리 정보 출력
    // type = 0 : 아이템 명, 아이템 설명, 아이템 개수, 골드 출력
    // type = 1 : 이름, 설명, 개수 출력
    // type = 2 : 이름, 설명 출력 
    player->inventoryComponent->displayInventory(0)

```



## 게임 시스템
---
### 개요
게임 시스템은 프로젝트에서 플레이어가 머무는 공간을 의미한다. Gamesystem 은 SystemContext 클래스를 통해 서로 다른 GameSystem으로 이동 및 현재 GameSystem에서 수행되어야 하는 기능을 호출하는 Update 함수를 통해 현재 System에 설정되어있는 SystemState에 맞는 기능을 수행한다.

### 주요 클래스
- SystemContext
- GameSystem
- LobbySystem
- LobbySystemStates
- BattleSystem
- BattleSystemStates
- ShopSystem

### SystemContext
SystemContext 클래스는 GameSystem을 상속받는 서브 클래스의 로직이 main 코드에서 반복문으로 실행 될 수 있도록 GameSystem::Update() 호출하는 클래스이다. 또한, 현재 플레이어가 위치한 GameSystem을 관리하는 기능을 수행한다. SystemContext는 GlobalEventManager를 통해 OnEvent로 호출된 기능을 수행한다.
- SystemContext(): SystemContext 생성자에서는 SystemContext가 관리할 각 GameSystem 멤버 변수들을 초기화하며, 첫 시작 System을 LobbySystem 으로 설정해 게임을 시작한다. 또한 GlobalEventManager에게 GameSystem(BattleSystem)을 등록해 추후 BattleSystem이 Event를 사용할 수 있도록 한다..
- OnEvent() override : SystemContext에 등록된 알맞은 Event인 경우 수행된다.
```C++
void SystemContext::OnEvent(const std::shared_ptr<IEvent> _event)
{
	if (auto move = std::dynamic_pointer_cast<IMoveSystemEvent>(_event)) // 플레이어 이동 이벤트 호출
	{
		MoveSystem(move->to, move->from);
	}
	else if (auto create = std::dynamic_pointer_cast<ICharacterCreateEvent>(_event)) // 플레이어 생성 이벤트 호출
	{
		CreateCharacter(create->name);
	}
	else if (auto gameOver = std::dynamic_pointer_cast<IPlayerDefeatEvent>(_event)) // 플레이어 패배 이벤트 호출
	{
		player.reset();
	}

	Publish(_event);
}
```
- Update(): 현재 설정된 Gamesystem의 로직을 호출하는 함수이다. GameSystem에 저장된 state에 맞는 virtual void ISystemState::Excute() 함수가 실행 되도록한다.
- MoveSystem(): GameSystem간 이동을 수행하는 함수이다.
```c++
oid SystemContext::MoveSystem(SystemType _to, SystemType _from)
{
	// System from 에서 System to 로 이동

	if (_to != _from)
	{
		switch (_to)
		{
		case SystemType::LOBBY:
			currentSystem = lobbySystem;
			break;
		case SystemType::BATTLE:
			currentSystem = battleSystem;
			break;
		case SystemType::SHOP:
			currentSystem = shopSystem;
			break;
		default:
			break;
		}

		currentSystem->EnterSystem();
	}
}
``` 

```c++
enum class SystemType
{
	LOBBY,
	BATTLE,
	SHOP
};

class SystemContext : public IEventManagerSystem
{
public:
	SystemContext();
	~SystemContext();

	SystemContext(const SystemContext&) = delete;
	SystemContext& operator=(const SystemContext&) = delete;

	void Update();

	void OnEvent(const std::shared_ptr<IEvent> _event) override;
	inline shared_ptr<class Player> GetPlayer() 
	{
		return player; 
	}

	shared_ptr<GameSystem> GetCurrentSystem()
	{ 
		return currentSystem; 
	}
private:
	void MoveSystem(SystemType _to, SystemType _from);

public:
	void CreateCharacter(string _name);

	shared_ptr<GameSystem> currentSystem = nullptr;

	shared_ptr<LobbySystem> lobbySystem;
	shared_ptr<BattleSystem> battleSystem;
	shared_ptr<ShopSystem> shopSystem;

	shared_ptr<Player> player;
};
```

```C++
	extern shared_ptr<SystemContext> GSystemContext;

	while (true)
	{
		GSystemContext->Update(); // Update()로 변경해야함
	}
```

[[목차로 돌아가기]](#목차)

---

### GameSystem
현재 플레이어가 위치한 공간을 의미하는 인터페이스 클래스이다. GameSystem을 상속 받는 서브 클래스로는 LobbySystem(로비 레벨), BattleSystem(전투 레벨), ShopSystem(상점 레벨)이 있으며
각 GameSystem은 현재 수행해야하는 State의 전환을 통해 어떤 기능을 수행해야할지 설정하고 GameSystem::Update() 함수가 호출되면 저장된 ISystemState 서브 클래스 기능에 맞게 팩토리된 클래스 로직을 Excute() 함수를 통해 수행합니다.
#### GameSystem의 역할

- 공통 인터페이스 제공
	-GameSystem은 다른 시스템이 반드시 구현해야 하는 메서드나 동작의 틀을 정의합니다. 이를 통해 시스템이 서로 다른 구현을 가지더라도, 일정한 인터페이스로 접근할 수 있습니다.

- 상태 관리 기능 제공
	- 모든 시스템이 상태 기반으로 동작하도록 설계되어 있어, 상태 변경과 동작이 명확히 구분됩니다.

- 유연한 확장성 보장
	-구체적인 기능은 각 하위 클래스 (BattleSystem, ShopSystem, ...)에서 구현하며, GameSystem은 이를 통제하는 역할을 합니다.

#### 주요 메서드
1. Update() : void 
	- 설명: 시스템의 state가 가진 기능을 실행합니다. 
	- 예시
		- BattleMainState->Update();
		- ShopSellState->Update();
```c++
void GameSystem::Update()
{
	//ChangeState();
	if (state)
	{
		state->Excute(this);
	}
	else
	{
		throw std::runtime_error("GameSystem의 state가 nullptr입니다.");
	}
}


```

2. EnterSystem() : void = 0;
	- 설명: 시스템이 활성화될 때 호출됩니다. 각 하위 클래스는 이를 구현하여 시스템별 초기화 작업을 수행합니다.
	- 예시
		- ShopSystem: 상점 아이템 리스트 초기화.

3. ExitSystem : void = 0;
	- 설명: 시스템이 비활성화될 때 호출됩니다. 시스템 종료 시 리소스를 정리하거나 다음 시스템으로 전환하는 역할을 합니다.
	- 예시
		- BattleSystem: 전투에서 사용된 몬스터 삭제
4. SetState(shared_ptr<ISystemState>)  void 및 + GetState() shared_ptr<ISystemState>
	- 설명: 현재 시스템의 상태를 관리하는 메서드입니다. 상태 변경(SetState) 및 현재 상태 조회(GetState)를 제공합니다.
	- 예시
		- BattleSystem에서 상태가 BattleAttackState로 전환되면 SetState를 호출.
```c++
class ISystemState
{
public:
	virtual ~ISystemState() = default;

	virtual void Excute(GameSystem* system) = 0;
};

class GameSystem : public IEventManagerSystem
{
public:
	inline virtual SystemType GetSystemType() = 0;
	
	virtual void EnterSystem() = 0; // 시스템이 시작될 때 수행될 함수(Initialize)
	void Update(); // system의 로직 수행을 수행하는 함수, 반복
	//void ExitSystem(SystemType nextType); // 시스템을 나가야할 때 수행할 함수
	virtual ~GameSystem() {};
	//virtual void ChangeState() = 0;
	void SetState(shared_ptr<ISystemState> _state) { state = _state; }
	virtual string GetSystemName() = 0;
protected:
	shared_ptr<ISystemState> state;
};

```
5. OnEvent void
	- 설명: 이벤트 기반 시스템과의 통신을 처리합니다.(EventManagerSystem을 상속) 하위 클래스에서 필요한 이벤트를 오버라이드하여 처리합니다.
	- 예시
		- BattleSystem: ICharacterDeadEvent 이벤트를 통해 캐릭터 사망 처리.
		- ShopSystem: IItemPurchasedEvent 이벤트를 통해 아이템 구매 처리.

#### 설계 특징
1. 템플릿 메서드 패턴
GameSystem의 메서드는 템플릿 메서드 패턴을 따릅니다.
이는 공통 로직을 상위 클래스에서 제공하고, 세부 구현은 하위 클래스에서 정의하도록 하는 방식입니다.

2. 상태 관리의 통합성
state라는 공통 속성을 사용해 모든 시스템이 상태 기반으로 동작하도록 설계되었습니다.
상태는 각각 ISystemState클래스의 하위 클래스로 정의됩니다.

3. 추상화와 구현의 분리
GameSystem은 인터페이스만 제공하며, 구체적인 로직은 하위 클래스에서 구현합니다.
이 방식은 코드 확장성과 유지보수성을 크게 향상시킵니다.

4. 이벤트 기반 설계
OnEvent 메서드를 통해 이벤트 시스템과 유연하게 통합됩니다.
이를 통해 시스템 간의 결합도를 낮추고, 이벤트 구독/발행 방식을 활용할 수 있습니다.

#### GameSystem의 장점
1. 일관된 인터페이스: 모든 시스템이 동일한 방식으로 접근 가능.
2. 유연한 확장성: 새로운 시스템 추가 시 GameSystem을 상속받아 구현하면 됨.
3. 캡슐화: 상태와 로직을 각 시스템 내부에 캡슐화하여, 다른 시스템과 독립적으로 작동 가능.
4. 유지보수 용이성: 공통 동작은 GameSystem에, 개별 동작은 하위 클래스에 구현되어 수정이 용이.

### LobbySystem
GameSystem을 상속받는 LobbySystem은 플레이어가 게임을 시작하거나, 게임 패배 혹은 승리 후 돌아올 때 위치하는 로비 공간을 의미힌다. 로비에서는 게임을 시작하가나 종료하고 게임을 시작할 경우 플레이어를 생성하는 기능을 수행한다.
- inline SystemType GetSystemType() override : 현재 플레이어가 위치한 로비의 값을 반환한다.
- MainMenu() : 플레이어에게 게임 시작, 게임 종료 메뉴를 출력한 뒤, 플레이어에게 입력을 받는다.
- CreatePlayerMenu() : 플레이어가 게임 시작시 플레이어의 이름을 입력 받고 입력 검증을 통해 플레이어 이름을 결정한다면, 이를 통해 초기 플레이어를 생성한다. 
```cpp
class LobbySystem : public GameSystem
{
public:

	LobbySystem();
	void EnterSystem() override;

	inline SystemType GetSystemType() override
	{ 
		return SystemType::LOBBY;
	}

	void OnEvent(const std::shared_ptr<IEvent> _event) override;

	void MainMenu();
	void CreatePlayerMenu();

	virtual string GetSystemName() override { return "로비"; };
private:
	std::vector<std::string> orcArt;
	std::vector<std::string> slimeArt;
	std::vector<std::string> dragonArt;
};
```
### LobbySystemStates
LobbySystem은 Update() 함수가 호출되면 현재 설정된 LobbySystemState 값에 맞는 기능을 호출하게 합니다. 
각 기능에 맞게 실행되도록 팩토리 패턴 방식을 적용하여, 같은 함수 여도 다른 기능이 수행되도록 합니다.
LobbyMainState: LobbySystem의 메인 메뉴가 실행 되도록 함.
LobbyCreateState: LobbySystem의 플레이어 생성이 실행 되도록 함.
```
class LobbyMainState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto lobby = dynamic_cast<LobbySystem*>(_system);

		if (lobby)
		{
			lobby->MainMenu();
		}
	}
};

class LobbyCreateState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto lobby = dynamic_cast<LobbySystem*>(_system);

		if (lobby)
		{
			lobby->CreatePlayerMenu();
		}
	}
};
```
### BattleSystemStates
- 개요
	- 플레이어가 전투를 진행하는 동안 생기는 이벤트들(공격 선택, 아이템 사용, 패배, 승리 등)에 대해 알맞은 기능을 수행하기 위해 구현한 클래스 입니다. 
 	- 플레이어가 전투 중 특정 전환을 수행할 때 state 멤버 변수를 변환해주면 다음에 Excute() 함수가 실행 될 때 의도한 기능이 수행 되도록 합니다
	- 각 State별 기능은 주석으로 설명하였습니다.
 ``` C++


class BattleMainState : public ISystemState // 플레이어의 전투 선택지를 출력합니다.
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->MainMenu();
		}
	}
};

class BattleAttackState : public ISystemState // 플레이어의 공격 메뉴를 호출합니다.
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->Attack();
		}
	}
};

class BattleDisplayState : public ISystemState // 플레이어의 전투중 현재 상태 및 스탯을 호출합니다.
{
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->DisplayStat();
		}
	}
};

class BattleUseItemState : public ISystemState // 플레이어의 아이템 사용 기능을 호출합니다. 보유 아이템을 출력합니다.
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->UseItem();
		}
	}
};

class BattleNextStageState : public ISystemState // 플레이어가 다음스테이지로 넘어갈 때 호출되는 기능입니다.
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->NextStage();
		}
	}
};

class BattleGameOverState: public ISystemState // 플레이어가 게임 종류 될 때 호출 되는 Battlesystem::GameOver() 함수입니다.
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* _system) override
	{
		auto battle = dynamic_cast<BattleSystem*>(_system);

		if (battle)
		{
			battle->GameOver();
		}
	}
};
 ```
[[목차로 돌아가기]](#목차)

---

### BattleSystem
- 개요
	- BattleSystem은 플레이어가 전투를 진행하는 공간입니다.
	- 

   
#### 주요 메서드
1. void OnEvent(const std::shared_ptr<IEvent> _event) override: BattleSystem에서 사용될 이벤트들이 OnEvent 함수 호출을 하면 이벤트에 맞는 로직을 수행하도록 분기문을 수행합니다. 
예를 들면 플레이어가 공격 받고 죽는다면 ICharacterDeadEvent 클래스 이벤트를 호출하고 BattleSystem이 GlobalEventManager::Notify()를 통해 호출 받는다면 BattleSystem::OnEvent() 함수에서 이를 처리하게 됩니다.
```C++
void BattleSystem::OnEvent(const std::shared_ptr<IEvent> _event)
{
	if (auto deadEvent = dynamic_pointer_cast<ICharacterDeadEvent>(_event))
	{
		auto player = GSystemContext->GetPlayer();
		if (monster->statManager->IsDead())
		{
			state = make_shared<BattleNextStageState>();
		}
		else if (player->statManager->IsDead())
		{
			state = make_shared<BattleGameOverState>();
		}
	}
	else if (auto turnEvent = dynamic_pointer_cast<ITurnStartEvent>(_event))
	{
		turnSystem->BeginTurn();
	}
}
```
2. BattleSystem(): 생성자 입니다. 전투 시스템에서 턴을 관리할 멤버 변수와 보상을 관리하는 멤버 변수를 초기화 해줍니다.
```C++
	shared_ptr<URewardEventManagerSystem> rewardSystem; // 플레이어가 승리시 골드, 경험치, 아이템, 스킬을 부여해주는 IEventMangerSystem을 상속받는 클래스 입니다.
	shared_ptr<UTurnEventManager> turnSystem; // 플레이어가 스킬 사용시 스킬의 지속시간, 쿨다운을 계산해주는 IEventMangerSystem을 상속받는 클래스 입니다.

BattleSystem::BattleSystem()
{
	rewardSystem = make_shared<URewardEventManagerSystem>();
	GlobalEventManager::Get().Subscribe(rewardSystem);

	turnSystem = std::make_shared<UTurnEventManager>();
	GlobalEventManager::Get().Subscribe(turnSystem);
}

```
3. virtual void EnterSystem() override : 플레이어가 전투 시스템에 처음 입장하면 전투 시스템의 시작 준비 기능을 수행합니다. 몬스터를 생성합니다. 이때 플레이어가 10레벨 이상인 경우 보스 몬스터를 생성합니다. 생성된 몬스터와 플레이어의 Target을 서로를 바로 보도록 설정하며 각자의 스킬이 Target에게 효과를 부여하도록 합니다.
```C++
void BattleSystem::EnterSystem()
{
	auto player = GSystemContext->GetPlayer();
	monster = make_shared<Monster>();
	monster->Initialize();
	monster->combatManager->SetTarget(player.get());
	player->combatManager->SetTarget(monster.get());

	player->combatManager->SetTarget(monster.get());

	activeCharacters.clear();
	activeCharacters.push_back(player.get());
	activeCharacters.push_back(monster.get());
	
	// 플레이어 레벨에 따른 monster 생성
	state = make_shared<BattleMainState>();

	rewardSystem->Initialize();
	turnSystem->TurnReset();
}
```
3.  MainMenu() : 플레이어가 매 턴 마다 수행할 선택지인 1. 공격, 2. 스탯확인, 3. 아이템 사용 메뉴를 출력하고 입력을 받습니다. 매 입력마다 검증을 수행합니다.
  ```C++
void BattleSystem::MainMenu()
{
	// 라운드 시작할때 몬스터 현재 상태 출력
	DisplayStat();

	int input = InputManagerSystem::GetInput<int>(
		"==== 전투 메뉴 ====",
		{ "1. 공격하기" ,"2. 아이템 사용하기" },
		RangeValidator<int>(1, 2)
	);

	if (input == 1)
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<BattleAttackState>()); // state->Excute() 가 공격을 수행하도록 변경 즉, BattleSystem::Attack을 수행하도록함
		GInvoker->ExecuteCommand(cmd);
		//state = make_shared<BattleAttackState>();
	}
	else
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<BattleUseItemState>());  // state->Excute() 가 아이템을 사용하도록 변경 즉, BattleSystem::UseItem() 수행하도록함
		GInvoker->ExecuteCommand(cmd);
		//state = make_shared<BattleUseItemState>();
	}
}
  ```

-  Attack(): 플레이어가 공격을 선택한다면 실행되는 함수이다. 플레이어가 가지고 있는 스킬 목록들을 선택지로 출력한 뒤, 플레이어에게 입력을 받는다. 입력이 알맞은지 검증 또한 수행합니다. 돌아가기 버튼을 누른다면 다시 MainState가 수행되도록 하며 스킬을 사용한 경우 대상에게 스킬 효과를 부여한다. 그리고 플레이어가 공격한다면 몬스터가 자동으로 반격하게 한다. 몬스터가 플레이어 상대로 공격하도록 몬스터의 공격 기능을 수행합니다. 각 공격은 수행시 플레이어와 몬스터의 사망 여부를 체크하고 사망시 이벤트 호출을 통해 다음 BattleSystemstate로 변환 될 작업인 BattleSystem::OnEvent() 함수를 수행하도록 구현했습니다.
  ```C++
void BattleSystem::Attack()
{
	auto battleitemcheck = make_shared<IPlayerBattleAttackEvent>(); // UIEvent로 플레이어 공격 수행 출력
	GlobalEventManager::Get().Notify(battleitemcheck);

	auto player = GSystemContext->GetPlayer();

	vector<string> activeSkillList = player->skillManager->GetActiveSkillInfoWithString(0);
	// Context로 부터 플레이어 목록 받아오기(System에서 player 저장 x)
	// 1~n: 가지고 있는 스킬
	// n+1: 돌아가기
	int returnButton = activeSkillList.size() + 1; // 돌아가기 버튼
	activeSkillList.push_back(to_string(returnButton) + ". 돌아가기");

	int input = InputManagerSystem::GetInput<int>(
		"==================  스킬 사용 ===================",
		activeSkillList,
		RangeValidator<int>(1, returnButton)
	);

	if (input == returnButton)
	{
		auto cmd = make_shared<SystemChangeStateCommand>(make_shared<BattleMainState>());
		GInvoker->ExecuteCommand(cmd);
		//state = make_shared<BattleMainState>();
		return; // mainstate 재실행=>공격,스탯,아이템 메뉴 재실행
	}
	else
	{ // 스킬 사용
		
		auto playerAttackEv = make_shared<IPlayerBattleAttackEvent>();
		GlobalEventManager::Get().Notify(playerAttackEv);

		auto player = GSystemContext->GetPlayer();

		state = make_shared<BattleMainState>();
		
		if (!player->skillManager->UseSkill(player->skillManager->GetActiveSkillNameByIndex(input - 1)))
		{
			state = make_shared<BattleMainState>();
			return;
		}
	}

	// 몬스터 공격
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "\n");
	monster->combatManager->SetTarget(player.get());

	auto monsterAttackEv = make_shared<IMonsterBattleAttackEvent>();
	GlobalEventManager::Get().Notify(monsterAttackEv);

	monster->skillManager->UseSkill("기본 공격");// 몬스터 죽으면 공격 안함
	
	turnSystem->EndTurn(activeCharacters);

	DisplayStat();

	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "\n");

	InputManagerSystem::PauseUntilEnter();
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);
}
  ```
  
-  DisplayStat(): 전투중 플레이어의 현재 상태를 출력합니다
  ```C++
void BattleSystem::DisplayStat()
{
	//CLEAR;
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftTop);
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::RightTop);
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftTop);
	ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::RightTop);

	auto player = GSystemContext->GetPlayer();
	player.get()->PrintCharacterInfo();
	monster.get()->PrintCharacterInfo(1);
}
  ```
-  UseItem(): 플레이어가 가지고 있는 현재 아이템 목록을 출력합니다. 아이템을 사용하거나 돌아간다면 다시 전투 메인메뉴를 출력하도록 합니다.
  ```C++
void BattleSystem::UseItem()
{
	//CLEAR;

	auto battleitemcheck = make_shared<IBattleUseItemEvent>();
	GlobalEventManager::Get().Notify(battleitemcheck);
	
	auto player = GSystemContext->GetPlayer();
	vector<string> itemList = player->inventoryComponent->GetInventoryInfoWithString(1);
	
	int lastIndex = itemList.size() + 1;

	itemList.push_back(to_string(lastIndex) +". 돌아가기");
	int input = InputManagerSystem::GetInput<int>(
		"=== 아이템 사용 ===", 
		itemList,
		RangeValidator<int>(1, lastIndex)
	);
  ```
-  NextStage(): 플레이어가 몬스터와의 전투에서 승리하면 호출되는 함수입니다. 처치한 몬스터가 보스인 경우 플레이어가 승리했다는 UI를 출력한 뒤 LobbySystem으로 돌아가도록 SystemContext::currentSystem 멤버 변수 값을 재설정합니다.
만약 플레이어가 일반 몬스터를 처치한 경우에는 플레이어에게 보상을 부여하는 GetReward() 함수를 호출한 다음 스테이지 또는 상점을 방문할 수있는 UI 출력 및 입력을 받습니다. 이때 입력을 검증합니다.

  ```C++
void BattleSystem::NextStage()
{
	if (monster->IsBoss())
	{	
		// 보스 몬스터
		// 게임 승리 UI 출력
		auto playergameclear = make_shared<IPlayerGameClearEvent>();
		GlobalEventManager::Get().Notify(playergameclear);

		// 게임 승리로 로비로 귀환,
		// 이때까지 동작한 로그라던가는 여기서 출력하시면 됩니다

		auto event = make_shared<IMoveSystemEvent>(SystemType::LOBBY, GetSystemType(), "로비", "배틀");
		GlobalEventManager::Get().Notify(event);
		InputManagerSystem::PauseUntilEnter();
		ConsoleLayout::GetInstance().SelectClear(ConsoleRegionType::LeftBottom);
		return;
	}
	else
	{	
		GetReward();

		int input = InputManagerSystem::GetInput<int>(
			"==== 스테이지 클리어 메뉴 ====",
			{ "1. 다음 스테이지" , "2. 상점 방문하기" },
			RangeValidator<int>(1, 2)
		);

		if (input == 1)
		{
			EnterSystem();
		}
		else if (input == 2)
		{
			auto cmd = make_shared<SystemMoveCommand>(SystemType::SHOP, GetSystemType(), "상점", "배틀");
			GInvoker->ExecuteCommand(cmd);
		}
	}
}
  ```
- GetReward() : 플레이어에게 보상을 부여하는 함수입니다. 플레이어는 일반 몬스터를 처치시 일반 몬스터가 가진 돈과 아이템을 받으며 경험치를 부여 받습니다. 또한 스킬을 선택해서 가질 수 있게 합니다.
```C++
void BattleSystem::GetReward()
{
	auto player = GSystemContext->GetPlayer();
	auto reward = rewardSystem->GetReward();

	player->inventoryComponent->addGold(reward.gold); // 돈 넣기

	if (monster->characterReward.dropItem != nullptr)
	{
		auto playergetitem = make_shared<IPlayerGetItemEvent>();
		GlobalEventManager::Get().Notify(playergetitem);
		player->inventoryComponent->addItem(reward.item); // 템 넣기
	}

	int skillSize = reward.skillTypes.size();
	
	if (reward.skillTypes.size() > 0)
	{
		vector<string> options;

		for (int i = 0; i < skillSize; i++)
		{
			shared_ptr<Skill> skill = SkillManager::GetInstance().CreateSkillFromType(reward.skillTypes[i], player.get());
			options.push_back(to_string(i + 1) + ", " + skill->GetSkillData().skillName);
		}

		int input = InputManagerSystem::GetInput<int>("=== 스킬 선택 ===", options, RangeValidator<int>(1, reward.skillTypes.size()));

		auto cmd = make_shared<AddSkillCommand>(reward.skillTypes[input - 1]);
		GInvoker->ExecuteCommand(cmd);
		Delay(1);
	}

	CharacterUtility::ModifyStat(player.get(), StatType::Experience, rewardSystem->GetReward().exp);
	monster = nullptr;

	auto battlestageclear = make_shared<IPlayerStageClearEvent>();
	GlobalEventManager::Get().Notify(battlestageclear);
}
```
-  GameOver() : 플레이어가 패배했을 시 호출 되는 함수입니다. 다시 로비로 되돌아 가도록 SystemContext의 OnEvent() 를 호출 하도록 GlobalEventManager::Notify()를 호출합니다.
  ```C++
void BattleSystem::GameOver()
{
	auto playergamedefeat = make_shared<IPlayerDefeatEvent>();
	GlobalEventManager::Get().Notify(playergamedefeat);

	auto event = make_shared<IMoveSystemEvent>(SystemType::LOBBY, GetSystemType(), "로비", "배틀");
	GlobalEventManager::Get().Notify(event);
}

  ```

[[목차로 돌아가기]](#목차)

---


---




---
### ShopSystem
도전과제의 상점 시스템을 구현한 것으로, 플레이어가 아이템을 사고팔고, 인벤토리와 관련된 작업을 처리하는 핵심적인 로직을 담당하고 있습니다. ShopSystem 은 아이템 구매, 판매, 인벤토리 관리 등의 기능을 처리하는 중요한 시스템입니다. 
플레이어의 상점 경험을 처리하는 중심적인 역할을 하며, UI와 사용자 입력을 잘 연결하여 게임의 흐름을 제어합니다. 이 시스템은 상태 패턴을 사용하여 상점의 여러 상태(메인 메뉴, 아이템 구매, 아이템 판매 등)를 처리하며, 각각의 상태 전환을 명령 패턴을 통해 실행하는 구조를 가집니다.

#### 주요 메서드
1. EnterSystem()
상점 시스템에 진입할 때 호출되는 함수로 진입 전 콘솔 화면을 전부 지우고, 랜덤 아이템과 스킬을 생성해 상점에서 판매할 아이템, 스킬을 준비합니다.

2. MainMenu()
상점의 메인 메뉴를 표시하고, 사용자의 선택을 처리합니다.
메인에선 아이템 구매, 판매, BattleSystem으로 돌아가기 중 하나를 선택하고, 선택된 입력에 따라 적절한 명령을 실행합니다. 

3. BuyItemMenu()
아이템 구매 메뉴를 표시하고, 사용자의 구매 요청을 처리합니다. 

4. SellMenu()
목적: 아이템 판매 메뉴를 표시하고, 사용자가 선택한 아이템을 판매합니다.

5. GetRandomItemsAndSkills()
목적: 랜덤 아이템과 스킬을 생성하여 상점에 추가합니다.

6. OnEvent()
캐릭터가 상점과 관련된 스킬(파는 아이템 가격 감소)을 획득할 때 해당 스킬에 대한 효과를 적용합니다.


[[목차로 돌아가기]](#목차)


---


---
# InputManagerSystem

**InputManagerSystem**은 사용자 입력을 관리하는 중요한 역할을 하며, 게임 내에서 플레이어의 동작을 처리하는 핵심적인 기능을 담당합니다. 이를 통해 게임 시스템과 유저 간의 상호작용을 연결합니다.

## InputManagerSystem의 역할
**InputManagerSystem**은 사용자로부터 입력을 받아 이를 게임 시스템의 적절한 동작으로 전환하는 역할을 합니다.
키보드 입력을 처리하고, 이를 다른 시스템에 전달하거나 특정 명령을 실행하게끔 합니다. 이 시스템은 다음과 같은 주요 기능들을 제공할 수 있습니다.

1. 입력 처리 및 검증: 사용자 입력을 받아 검증하고 검증 결과가 부합하면 값을 반환합니다.
2. 입력 대기 및 전환: 입력을 기다리고, 특정 입력에 따라 상태나 시스템을 전환하는 기능을 담당합니다.
3. 사용자 인터페이스 관리: 입력을 받아 UI 메뉴를 구성하고, 사용자 선택에 따라 다른 시스템으로의 전환을 유도할 수 있습니다.
4. 범용성: 입력 처리 시스템이 다양한 게임 시스템에서 공통적으로 사용할 수 있도록 설계됩니다.

## InputManagerSystem의 구성 및 흐름
```cpp
class InputManagerSystem {
public:
    template <typename T>
    static T GetInput(const std::string& prompt, const std::vector<std::string>& options, const RangeValidator<T>& validator);

    static void PauseUntilEnter();  // 엔터키가 입력될 때까지 대기
};
```
### + GetInput<T>() 
사용자로부터 입력을 받아 해당 타입(`T`)에 맞는 값을 반환합니다. options로 제공된 선택지들 중 하나를 선택하게 하거나, 특정 범위 내에서 값이 입력되도록 검증할 수 있습니다.
InputValidator 객체를 사용하여 입력값이 유효한 범위 내에 있는지 확인합니다. 가변 인자 템플릿이기에, 하나의 입력에 대한 검증에 여러가지 검증 조건을 추가해줄 수 있습니다.
범용성: 다양한 타입에 대해 GetInput을 사용할 수 있도록 템플릿으로 설계되었습니다. 예를 들어, 정수형, 문자열, 등 다양한 타입에 대해 동작합니다.

#### 사용 예시
```cpp
string userName = InputManagerSystem::GetInput(
	"캐릭터의 이름을 입력해주세요.(중간 공백 허용, 최대12자)",
	{},
	NameRangeValidator(1, 12),
	NameSpaceValidator(),
	NoSpecialCharValidator()
);
```
`NameRangeValidator(1,12)` 는 `string.length()`를 기준으로 범위를 검증합니다.
`NoSpaceValidator()` 는 입력 받은 string이 전부 공백인지 확인합니다.
`NoSpecialCharValidator()` 는 특수문자 입력을 방지합니다.

즉 위의 함수는 사용자에게 `string` 입력을 받고, 입력값의 길이가 1~12 인지, 전부 공백이 아닌지, 특수문자가 포함되지 않은지 확인하고 모든 조건이 `true`일 때 `userName`에 값을 리턴해줍니다.

### + PauseUntilEnter 메서드
이 메서드는 사용자가 Enter 키를 누를 때까지 대기하는 기능을 수행합니다.
일반적으로 게임의 특정 화면에서 UI 이벤트나 상태 전환 후 사용자의 입력을 기다릴 때 사용됩니다.

### InputManagerSystem의 사용 사례
`InputManagerSystem`은 다양한 시스템에서 사용자 입력을 처리하는 역할을 합니다. 몇 가지 주요 사용 사례는 다음과 같습니다.

1. 각 시스템에서의 분기 입력 
각 시스템에서 분기를 선택해야 할 때, 입력을 처리합니다.

```cpp
//배틀 시스템에서의 분기 선택 예시
int input = InputManagerSystem::GetInput<int>(
    "==== 전투 메뉴 ====",
    { "1. 공격하기", "2. 아이템 사용하기" },
    RangeValidator<int>(1, 2)
);

//상점 시스템에서의 분기 선택 예시
int input = InputManagerSystem::GetInput<int>(
    "=== 아이템 구매 ===", 
    itemList,
    RangeValidator<int>(1, lastIndex)
);
```

2. UI 메뉴 선택
게임의 여러 메뉴에서 사용자의 선택을 받습니다. 예를 들어, 퀘스트 선택, 옵션 메뉴에서의 설정 변경 등이 가능합니다.

```cpp
int input = InputManagerSystem::GetInput<int>(
    "=== 스킬 선택 ===",
    options,
    RangeValidator<int>(1, reward.skillTypes.size())
);
```
### InputManagerSystem의 장점
- 유연성: 다양한 게임 시스템에서 재사용할 수 있도록 설계되었습니다. 템플릿 메서드를 사용하여 다양한 타입의 입력을 받을 수 있습니다.
- 사용자 입력의 검증: RangeValidator와 같은 검증 메커니즘을 사용하여, 잘못된 입력을 처리하고 유효한 입력만을 허용합니다.
- 인터페이스와의 결합도 감소: InputManagerSystem을 통해 UI와 관련된 로직을 분리하고, 게임 시스템의 로직은 입력 처리에 집중할 수 있습니다.
- 입력 대기 기능: PauseUntilEnter 메서드를 통해 사용자가 입력을 완료할 때까지 대기하는 기능을 제공합니다. 이는 특정 상황에서의 대기 또는 정지 동작에 유용합니다.

### 개선 가능성
- 입력 처리 확장: 현재는 텍스트 기반의 입력만 처리하는 것으로 보이는데, 게임이 발전함에 따라 마우스 클릭, 드래그 등의 입력도 지원할 수 있습니다.
- 실행 처리 확장: 현재는 입력값을 반환하지만, 각 분기별 실행 기능을 같이 넣어 입력 값을 반환하지 않고 입력 값에 대한 추가적인 동작을 지원할 수 있습니다.

### 결론
InputManagerSystem은 게임에서 유저 인터페이스(UI)와 시스템 간의 중요한 연결 고리 역할을 합니다. 사용자로부터 입력을 받아 이를 검증하고, 적절한 시스템 동작을 유도하는 방식으로 게임의 흐름을 자연스럽게 제어합니다. 특히 다양한 입력을 처리하는 유연성과 검증 메커니즘을 통해 게임 시스템을 안정적으로 동작시킬 수 있는 중요한 역할을 합니다.


[[목차로 돌아가기]](#목차)

---


## 코드 시연 영상
[![Video Label](http://img.youtube.com/vi/LgUdFP0pCiY/0.jpg)](https://youtu.be/LgUdFP0pCiY)




## KPT회고 













