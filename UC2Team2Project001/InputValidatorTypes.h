#include "pch.h"
#include <regex>

#define MAX_NAME_LENGTH 12

// input 대한 조건을 검사하는 클래스입니다.
template<typename T>
class InputValidator
{
public:
	virtual ~InputValidator() = default;

	// 유효성 검사를 담당하는 함수입니다. 실패할 경우 자동으로 오류 메시지 출력합니다.
	bool IsValidate(const T& input) const
	{
		if (!IsValid(input)) {
			PrintErrorMessage();  // 유효하지 않으면 오류 메시지를 출력
			return false;
		}
		return true;
	}

protected:
	// 유효성 검사 로직은 자식 클래스에서 정의해주세요.
	virtual bool IsValid(const T& input) const = 0;

	// 오류 메시지를 출력하는 함수입니다. 마찬가지로 자식 클래스에서 정의해주세요.
	virtual void PrintErrorMessage() const = 0;
};

// 입력이 필요 없는 경우가 생길 경우 해당 클래스를 이용해주세요
template<typename T>
class NoValidator : public InputValidator<T>
{
public:
	NoValidator() {};
	virtual bool IsValid(const T& input) const { return true; } ;
	virtual void PrintErrorMessage() const {} ;
};

// 범위 검사 최소, 최댓값을 매개변수로 받습니다.
template<typename T>
class RangeValidator : public InputValidator<T>
{
public:
	RangeValidator(T min, T max) : min(min), max(max) {}

protected:
	bool IsValid(const T& input) const override
	{
		return (input >= min) && (input <= max);
	}

	void PrintErrorMessage() const override
	{
		std::cout << "입력 값은 " << min << "과 " << max << " 사이여야 합니다.\n";
	}

private:
	T min, max;  // 최소값과 최대값
};

// 이름 길이 검증 클래스, 위와 비슷하지만 string의 length를 검사합니다
class NameRangeValidator : public InputValidator<string>
{
public:
	NameRangeValidator(int min = 0, int max = MAX_NAME_LENGTH) : min(min), max(max) {}

protected:
	bool IsValid(const string& input) const override
	{
		return (input.length() >= min) && (input.length() <= max);
	}

	void PrintErrorMessage() const override
	{
		std::cout << "이름은 " << min << "자 이상 " << max << "자 이하로 입력해야 합니다.\n";
	}

private:
	int min, max;  // 최소 길이와 최대 길이
};
// 이름에 공백만 들어간 경우를 검증함
class NameSpaceValidator : public InputValidator<string>
{
public:
	NameSpaceValidator() {}

protected:
	bool IsValid(const string& input) const override
	{
		return !std::all_of(input.begin(), input.end(), [](const char c)
			{ 
				return std::isspace(c);
			});
		// std::all_of: iterator 구간 사이 모든 인자가 조건문을 만족하는 경우 true 아닌 경우 false
		// isspace(): 공백인경우 true 반환
		// => 모든 이름이 공백으로만 되어있는 경우 true를 반환
		// !를 붙여 이름이 전부 공백이면 검증 통과를 못하도록 함
	}

	void PrintErrorMessage() const override
	{
		std::cout << "이름이 전부 공백으로 입력되어있습니다.\n";
	}

private:

};

class NoSpecialCharValidator : public InputValidator<string>
{
public:
		

protected:
	bool IsValid(const string& input) const override
	{
		// 정규식 패턴: 알파벳 대소문자, 숫자, 공백만 허용
		return regex_match(input, regex("^[a-zA-Z0-9 ]*$"));
	}

	void PrintErrorMessage() const override
	{
		std::cout << "입력값에 특수문자가 포함되어 있습니다.\n";
	}
};

class RegexValidator : public InputValidator<string>
{
public:
	// 정규식 패턴과, 정규식이 일치하지 않을 경우 출력할 오류 메시지를 넣어주세요.
	RegexValidator(const string& pattern, const string& errorMessage = "입력값이 규칙과 맞지 않습니다.\n")
		: errorMessage(errorMessage) 
	{
		regexPattern = regex(pattern);
	}

protected:
	bool IsValid(const string& input) const override
	{
		return regex_match(input, regexPattern);
	}

	void PrintErrorMessage() const override
	{
		std::cout << errorMessage;
	}

private:
	regex regexPattern;
	string errorMessage;
};
