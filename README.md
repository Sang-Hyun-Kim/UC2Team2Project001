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
  ![Image](https://github.com/user-attachments/assets/42e664dd-1a6e-4bb5-925e-e050a6328a21)

```C++
// 코드블록(언어 C++)
```
