# 팀명: Auto
---
## 프로젝트 명: 뒷 동네 마왕 잡으러 가기
## 프로젝트 개요
  - 프로젝트 작업 기간: 2025/01/10 ~ 2025/01/16
  - C++ 디자인 패턴을 적용한 객체 지향 방식 TEXT RPG 게임을 만들고 싶었습니다. 저희가 구현하고자 하는 기능 과 시스템이 코드 재사용, 확장성, 유지 보수성을 가지려면 어떻게 구현해야하는지 기획, 설계 한 뒤 이를 구현하는 과정을 가졌습니다. 
## 주요 기능 요약
  - 로비, 전투, 상점을 기능하는 GameSystem 서브 클래스들을 제작했고, 모든 System을 괸리하는 SystemContext가 Update 함수를 통해 어느 GameSystem 이든 실행하고 플레이어가 방을 이동하는 방식으로 구현
  - 플레이어가 수동 전투를 진행하며 스킬과 아이템을 자유롭게 사용함
  - 플레이어에게 턴 시스템을 부여하여 스킬과 아이템이 적용하는 효과와 Cooldown 시스템이 Turn을 가지도록 구현
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
    
### 주요 기능 설명
---


---
```C++
// 코드블록(언어 C++)
```
## 코드 시연 영상
[![Video Label](http://img.youtube.com/vi/LgUdFP0pCiY/0.jpg)](https://youtu.be/LgUdFP0pCiY)








# 스킬 시스템 문서

## 개요
이 프로젝트의 **스킬 시스템**은 캐릭터의 스킬을 관리하기 위한 강력하고 확장 가능한 프레임워크를 제공합니다. 액티브 스킬과 패시브 스킬, 스킬 조건, 효과, 행동을 지원하며, 모듈성과 재사용성을 극대화하여 다른 부분에 영향을 주지 않고도 스킬을 추가, 수정, 삭제할 수 있습니다.

##목표
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

---






