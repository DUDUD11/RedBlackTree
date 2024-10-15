#include "STDString.h"

namespace AppShift {
	STDString::STDString(const char* str)
	{
		this->length = strlen(str);
		this->start = new char[this->length];
		memcpy(this->start, str, this->length);
	}

	STDString::~STDString() { delete this->start; }

	char* STDString::data() const { return this->start; }

	size_t STDString::size() const { return this->length; }

	STDString& STDString::operator=(const char* str)
	{
		delete this->start;
		this->length = strlen(str);
		this->start = new char[this->length];
		memcpy(this->start, str, this->length);
		return *this;
	}

	STDString& STDString::operator=(const STDString& str)
	{
		delete this->start;
		this->length = str.size();
		this->start = new char[this->length];
		memcpy(this->start, str.data(), this->length);
		return *this;
	}

	STDString& STDString::operator+=(const char* str)
	{
		int add_length = strlen(str);
		char* str_holder = new char[this->length + add_length];
		memcpy(str_holder, this->start, this->length);
		memcpy(str_holder + this->length, str, add_length);
		delete this->start;
		this->start = str_holder;
		this->length += add_length;
		return *this;
	}

	STDString& STDString::operator+=(const STDString& str)
	{
		char* str_holder = new char[this->length + str.size()];
		memcpy(str_holder, this->start, this->length);
		memcpy(str_holder + this->length, str.data(), str.size());
		delete this->start;
		this->start = str_holder;
		this->length += str.size();
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const STDString& str)
	{
		os << str.data();
		os.flush();
		return os;
	}
}