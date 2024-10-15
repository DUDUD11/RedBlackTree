#pragma once
#include <Windows.h>
#include <wchar.h>
#include <cstdint>
#include <stdexcept>
#define map_size 100
#define name_len 64
#define Writing_Period 1000
#define Profile_File_Name "Profiler.txt"

class Profile
{
private:
	const wchar_t* name;
	void Start(const wchar_t* tag);
	void End();
	int Profile_Writing_Period=1000;

public:
	Profile(const wchar_t* tag,int period = Writing_Period);
	~Profile();


};
struct st_profile;

void timer_init();
void Profile_Reset();
st_profile* find(const wchar_t* tag);
bool File_Write();
bool Add(st_profile* data);

