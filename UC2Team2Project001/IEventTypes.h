#pragma once

#include <string>
#include <memory>

using namespace std;

// 모든 이벤트의 공통 부모
class IEvent
{
public:
	virtual ~IEvent() = default;
};




#pragma region 더미코드

//enum class EEventType
//{
//	CharacterDamaged,
//	CharacterDead,
//	ItemPurchased,
//	// ...
//};
//
//struct CharacterDamagedPayload
//{
//	std::string CharacterName;
//	int Damage;
//	int HP;
//};
//
//struct CharacterDeadPayload
//{
//	std::string CharacterName;
//	FCharacterReward Reward;
//};
//
//struct ItemPurchasedPayload
//{
//	std::string BuyerName;
//	std::string ItemName;
//	int Cost;
//};
//
//// ...
//using EventPayload = std::variant<CharacterDamagedPayload,
//	CharacterDeadPayload,
//	ItemPurchasedPayload,
//	/* ... */>;
//
//class GameEvent
//{
//public:
//	EEventType Type;
//	EventPayload Payload;
//
//	GameEvent(EEventType InType, const EventPayload& InPayload)
//		: Type(InType), Payload(InPayload)
//	{
//	}
//};
#pragma endregion 더미코드



