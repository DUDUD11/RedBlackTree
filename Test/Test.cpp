// Test.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>
#include "RBTree.h"
#include "Memory_Pool.h"
#include "Serial_Buffer.h"


#include "MemoryPool_copy.h"
#include "String.h"
#include "STDString.h"
#include <time.h>

#include "profiler.h"
#include <set>


using namespace MemoryPool;

struct example
{
    int x;
    int y;
    int z;
    float xx;
    float yy;
    float zz;

    example()
    {
        x = 0;
        y = 0;
        z = 0;
        xx = 0.0f;
        yy = 0.0f;
        zz = 0.0f;
    }

    ~example()
    {
        x = 0;
        y = 0;
        z = 0;
        xx = 0.0f;
        yy = 0.0f;
        zz = 0.0f;
    
    
    }

};
//https://github.com/DevShiftTeam/AppShift-MemoryPool/tree/main

int main()
{
    /*
    LARGE_INTEGER timer, start, end;
    
    QueryPerformanceFrequency(&timer);
    const int num = 100000;
    example* bucket[num];
    example* bucket_pool[num];


    */
    timer_init();
    int N = 10;
    
    for (int i = 0; i < N; i++)
    {



        RBTree<int> tree;
        std::set<int> int_set;

        int M = 1000000;

        {
            Profile p(L"hand made_insert", N);

            for (int i = 1; i < M; i++)
            {
                tree.insert(i);
            }
        }


        {
            Profile p(L"STL_insert", N);

            for (int i = 1; i < M; i++)
            {
                int_set.insert(i);

            }


        }


        {
            Profile p(L"hand made_delete", N);

            for (int i = 1; i < M; i++)
            {
                tree.remove(i);

            }
        }


        {
            Profile p(L"STL_delete", N);

            for (int i = 1; i < M; i++)
            {
                int_set.erase(i);
            }
        }

    }
  
    
    /*
    CPacket* cPacket = new CPacket();
    
    struct st_NETWORK_PACKET_HEADER
    {
        int x;
        int y;
        int z;



    };

    /*
    st_NETWORK_PACKET_HEADER	stPacketHeader;
    stPacketHeader.x = 1;
    stPacketHeader.y = 5;
    stPacketHeader.z = 10;

    cPacket->PutData((char*)&stPacketHeader, sizeof(stPacketHeader));
    
    unsigned char a = 250;
    char b = 'b';

    short c = -25000;
    unsigned short d= 65000;
    int e = 999999;
    long f = 1234;
    float g = 10.9f;
    __int64 h = 3000000000;
    double i = 97897.3;

    BYTE aa;
    char bb;
    short cc;
    WORD dd;
    int ee;
    DWORD ff;
    float gg;
    __int64 hh;
    double ii;

    *cPacket <<a<<b<<c<<d<<e<<f<<g<<h<<i;
     
    *cPacket >>aa>>bb>>cc>>dd>>ee>>ff>>gg>>hh>>ii;

    printf("hello!\n");
    */
    /*
    CMemoryPool<example> pool(300,true);

    example* ex =pool.Alloc();

    ex->x = 1;

    example* ex2 = pool.Alloc();

    ex2->x = 2;

    pool.Free(ex);

    pool.Free(ex2);

    example* ex3 = pool.Alloc();

    pool.Free(ex3);
    */

 /*
    for (int i = 0; i < 10000; i++)
    {


        printf("num size %d\n", num);

        QueryPerformanceCounter(&start);
        CMemoryPool <example> memorypool(num, false);
        QueryPerformanceCounter(&end);

        printf("memorypool init %f\n", (end.QuadPart - start.QuadPart) / (double)timer.QuadPart);

        QueryPerformanceCounter(&start);

        for (int i = 0; i < num; i++)
        {
            bucket[i] = new example();
        }

        QueryPerformanceCounter(&end);

        printf("new %f\n", (end.QuadPart - start.QuadPart) / (double)timer.QuadPart);

        QueryPerformanceCounter(&start);
        for (int i = 0; i < num; i++)
        {
            bucket_pool[i] = memorypool.Alloc();
        }
        QueryPerformanceCounter(&end);
        printf("memorypool alloc %f\n", (end.QuadPart - start.QuadPart) / (double)timer.QuadPart);


        QueryPerformanceCounter(&start);
        for (int i = 0; i < num; i++)
        {
            delete(bucket[i]);
        }

        QueryPerformanceCounter(&end);
        printf("new dealloc %f\n", (end.QuadPart - start.QuadPart) / (double)timer.QuadPart);

        QueryPerformanceCounter(&start);
        for (int i = 0; i < num; i++)
        {
            memorypool.Free(bucket_pool[i]);
        }

        QueryPerformanceCounter(&end);
        printf("memorypool dealloc %f\n", (end.QuadPart - start.QuadPart) / (double)timer.QuadPart);

        Sleep(10);

    }
    */

/*

AppShift::MemoryPool* mp = new AppShift:: MemoryPool();

clock_t t;
long double benchavg = 0;
long double benchavg_new = 0;


for (long long int j = 0; j < 10; j++) {
    t = clock();
    for (int i = 0; i < 1000000; i++) {
        AppShift::String strs(mp, "The Big World Is Great And Shit"); // Allocation
        strs += "Some new stuff"; // Re-allocation
    } // Dellocation
    t = clock() - t;
    benchavg += (t / (j + 1)) - (benchavg / (j + 1));
}

std::cout << "AppShift Library: " << (benchavg * 1000) / CLOCKS_PER_SEC << std::endl;

for (long long int j = 0; j < 10; j++) {
    t = clock();
    for (int i = 0; i < 1000000; i++) {
        AppShift::STDString strs("The Big World Is Great And Shit"); // Allocation
        strs += "Some new stuff"; // Re-allocation
    } // Dellocation
    t = clock() - t;
    benchavg_new += (t / (j + 1)) - (benchavg_new / (j + 1));
}

std::cout << "AppShift Library with regular new/delete: " << (benchavg_new * 1000) / CLOCKS_PER_SEC << std::endl;
std::cout << "MemoryPool is " << benchavg_new / benchavg << " Times faster than new/delete" << std::endl;

benchavg = 0;
for (long long int j = 0; j < 10; j++) {
    t = clock();
    for (int i = 0; i < 1000000; i++) {
        std::string strs("The Big World Is Great And Shit"); // Allocation
        strs += "Some new stuff"; // Rellocation
    } // Dellocation
    t = clock() - t;
    benchavg += (t / (j + 1)) - (benchavg / (j + 1));
}

std::cout << "Standard Library: " << (benchavg * 1000) / CLOCKS_PER_SEC << std::endl;
*/
return 0;
}




// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
