#pragma once

#include "MemoryPool_copy.h"
#include <ostream>
#include <cstring>

namespace AppShift {
	class STDString {
	public:
		STDString(const char* str = "");
		~STDString();

		char* data() const;
		size_t size() const;

		STDString& operator=(const char* str);
		friend std::ostream& operator<<(std::ostream& os, const STDString& dt);
		STDString& operator=(const STDString& str);
		STDString& operator+=(const char* str);
		STDString& operator+=(const STDString& str);

	private:
		char* start;
		size_t length;
	};
}