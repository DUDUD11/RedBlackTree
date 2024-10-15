#pragma once

#include "MemoryPool_copy.h"
#include <ostream>
#include <cstring>

namespace AppShift {
	class String {
	public:
		String(AppShift::MemoryPool* mp, const char* str = "");
		~String();

		char* data() const;
		size_t size() const;

		String& operator=(const char* str);
		friend std::ostream& operator<<(std::ostream& os, const String& dt);
		String& operator=(const String& str);
		String& operator+=(const char* str);
		String& operator+=(const String& str);

	private:
		char* start;
		size_t length;
		AppShift::MemoryPool* mp;
	};
}