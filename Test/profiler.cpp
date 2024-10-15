#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include "Profiler.h"



struct st_profile
{
	short			Flag;				// 0이면 초기상태, 1이면 열린, -1이면 닫힌
	wchar_t			szName[name_len];			// 프로파일 샘플 이름.

	LARGE_INTEGER	lStartTime;			// 프로파일 샘플 실행 시간.

	double			iTotalTime;			// 전체 사용시간 카운터 Time.	(출력시 호출회수로 나누어 평균 구함)
	double			iMin;			// 최소 사용시간 카운터 Time.	(초단위로 계산하여 저장 / [0] 가장최소 [1] 다음 최소 [2])
	double			iMax;			// 최대 사용시간 카운터 Time.	(초단위로 계산하여 저장 / [0] 가장최대 [1] 다음 최대 [2])

	__int64			iCall;				// 누적 호출 횟수.

};


st_profile profile_map[map_size] = { 0, };
LARGE_INTEGER Freq;
INT64 Num_Counter = 0;
FILE* fp;

void timer_init()
{
	QueryPerformanceFrequency(&Freq);
	//	memcpy(profile_map, 0, sizeof(profile_map));
}

void Profile_Reset()
{
	//초기화

}

st_profile* find(const wchar_t* tag)
{
	for (int i = 0; i < map_size; i++)
	{
		if (wcscmp(profile_map[i].szName, tag) == 0)
		{
			return &profile_map[i];
		}

	}

	return nullptr;

}

bool File_Write()
{
	fp = fopen(Profile_File_Name, "w");
	wchar_t buffer[10000] = { 0, };

	int num;

	num = swprintf(buffer, L"        Name      |     Average  |        Min   |        Max   |      Call |\n");
	num += swprintf(buffer + num, L"---------------------------------------------------------------------------\n");

	for (int i = 0; i < map_size; i++)
	{
		if (profile_map[i].Flag != 0) // 멀티스레드에서는 열린상태도 처리해야될듯
		{
			num += swprintf(buffer + num, L"%18s", profile_map[i].szName);
			num += swprintf(buffer + num, L"%12fms", profile_map[i].iTotalTime / (profile_map[i].iCall));
			num += swprintf(buffer + num, L"%12fms", profile_map[i].iMin);
			num += swprintf(buffer + num, L"%12fms", profile_map[i].iMax);
			num += swprintf(buffer + num, L"%10lld\n", profile_map[i].iCall);
		}
	}

	fwrite(buffer, sizeof(buffer), 1, fp);

	fclose(fp);

	return true;
}

bool Add(st_profile* data)
{
	for (int i = 0; i < map_size; i++)
	{
		if (profile_map[i].Flag == 0)
		{
			memcpy(&profile_map[i], data, sizeof(st_profile));
			return true;
		}

	}




	return false;
}

void Profile::Start(const wchar_t* tag)
{

	name = tag;

	st_profile* temp = find(tag);



	if (temp == nullptr)
	{
		st_profile obj;
		obj.Flag = 1;
		wcsncpy(obj.szName, tag, name_len);

		QueryPerformanceCounter(&obj.lStartTime);
		obj.iTotalTime = 0;
		obj.iMax = 0;
		obj.iMin = DBL_MAX;
		obj.iCall = 0;

		if (!Add(&obj))
		{
			throw std::runtime_error("Profile Map Not Write");
		}
	}

	else
	{

		if (temp->Flag == 1)
		{
			throw std::runtime_error("Profile Not Closed");

		}

		temp->Flag = 1;
		QueryPerformanceCounter(&temp->lStartTime);


	}



}

void Profile::End()
{

	LARGE_INTEGER end;
	double DeltaTime;
	st_profile* temp = find(name);

	if (temp == nullptr)
	{
		throw std::runtime_error("Profile Not Found");

	}

	if (temp->Flag != 1)
	{
		throw std::runtime_error("Profile Not Opened");

	}

	QueryPerformanceCounter(&end);
	temp->Flag = -1;
	DeltaTime = (double)(end.QuadPart - temp->lStartTime.QuadPart) / (double)Freq.QuadPart;
	DeltaTime *= 1000; // second 에서 millisecond로 변환
	temp->iTotalTime += DeltaTime;
	temp->iCall = temp->iCall + 1;
	temp->iMax = max(temp->iMax, DeltaTime);
	temp->iMin = min(temp->iMin, DeltaTime);

	Num_Counter++;

	
	if (Num_Counter % Profile_Writing_Period == 0)
	{
		if (!File_Write())
		{
			throw std::runtime_error("File Not Writed");

		}

	}
	



}

Profile::Profile(const wchar_t* tag, int period)
{
	Start(tag);
	name = tag;
	Profile_Writing_Period = period;
}

Profile::~Profile()
{
	End();
}


