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
    
# 주요 기능 설명
---

## 목차

1. [주요 기능](#주요-기능)
2. [핵심 클래스 및 컴포넌트](#핵심-클래스-및-컴포넌트)
   - [Character (기본 클래스)](#1-character-기본-클래스)
   - [Player (파생 클래스)](#2-player-파생-클래스)
   - [Monster (파생 클래스)](#3-monster-파생-클래스)
   - [UStatsComponent](#4-ustatscomponent)
   - [UCombatComponent](#5-ucombatcomponent)
   - [StatsLoader](#6-statsloader)
3. [사용 예시](#사용-예시)
4. [JSON 구조](#json-구조)
5. [시스템 확장 방법](#시스템-확장-방법)


## 캐릭터 시스템 개요

- 이 프로젝트는 플레이어, 몬스터, 보스 등 다양한 캐릭터 타입을 관리하기 위해 설계된 **캐릭터 시스템**입니다. 이 시스템은 스탯, 스킬, 전투 메커니즘 및 보상 관리를 모듈식으로 처리하며, 확장성과 유지보수성을 염두에 두고 설계되었습니다.

---
##클래스 다이어그램

![image](https://github.com/user-attachments/assets/bb0d8961-b49d-4493-861a-71fed4931fb9)

![image](https://github.com/user-attachments/assets/ae78ced7-0324-4824-b3f6-e495b9a9f84e)


## 주요 기능

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

## 핵심 클래스 및 컴포넌트

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

---




---
```C++
// 코드블록(언어 C++)
```
## 코드 시연 영상
[![Video Label](http://img.youtube.com/vi/LgUdFP0pCiY/0.jpg)](https://youtu.be/LgUdFP0pCiY)














# 상태 시스템 문서

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

# 아이템 시스템 문서 


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

