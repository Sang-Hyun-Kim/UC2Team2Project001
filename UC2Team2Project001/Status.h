#pragma once
class Status
{
	Status()
	{

	}
private:
	// ���� �ð�
	int Duration;

public:
	// �������ͽ� ����
	virtual void ApplyStatus();

	// ���� �ð�
	int GetDuration();
};

