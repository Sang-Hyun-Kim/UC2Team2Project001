#pragma once
class Status
{
private:
	// ���� �ð�
	int Duration;

public:
	// �������ͽ� ����
	virtual void ApplyStatus();

	// ���� �ð�
	int GetDuration();
};


// ����
class Berserker : Status
{
	// ���� ��� ����
	void ApplyStatus()
	{

	}
};

