#pragma once
class Status
{
private:
	// 지속 시간
	int Duration;

public:
	// 스테이터스 적용
	virtual void ApplyStatus();

	// 적용 시간
	int GetDuration();
};


// 예시
class Berserker : Status
{
	// 적용 방법 구현
	void ApplyStatus()
	{

	}
};

