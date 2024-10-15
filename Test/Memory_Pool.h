#pragma once

#ifndef  __PROCADEMY_MEMORY_POOL__
#define  __PROCADEMY_MEMORY_POOL__
#include <new.h>

/*---------------------------------------------------------------

	procademy MemoryPool.

	메모리 풀 클래스 (오브젝트 풀 / 프리리스트)
	특정 데이타(구조체,클래스,변수)를 일정량 할당 후 나눠쓴다.

	- 사용법.

	procademy::CMemoryPool<DATA> MemPool(300, FALSE);
	DATA *pData = MemPool.Alloc();

	pData 사용

	MemPool.Free(pData);

	// placement new 이면 node 뒷부분에 초기화여부를 넣는다.
----------------------------------------------------------------*/

namespace MemoryPool
{

	template <class T>
	class CMemoryPool
	{
		struct Node
		{
			T Data; //data를 가져야할듯
			bool initial;
			Node* NextNode;

			Node()
			{
				
			}

			~Node()
			{
			
			}

		};

	private:
		bool PlacementNew;
		int Capacity;
		int UseCount;
		Node* curNode = nullptr;

		// 스택에 넣을때 wrapper로 감싸서 자신의 T인지 확인하는 것을 넣어도 좋음
	public:

		//////////////////////////////////////////////////////////////////////////
		// 생성자, 파괴자.
		//
		// Parameters:	(int) 초기 블럭 개수.
		//				(bool) Alloc 시 생성자 / Free 시 파괴자 호출 여부
		// Return:
		//////////////////////////////////////////////////////////////////////////
		CMemoryPool(int iBlockNum, bool bPlacementNew = false)
		{
			Capacity = iBlockNum;
			PlacementNew = bPlacementNew;
			UseCount = 0;

			for (int i = 0; i < iBlockNum; i++)
			{
				Node* node = new Node();
				node->NextNode = curNode;
				node->initial = false;
				curNode = node;
			}
		}

		/*
		virtual	~CMemoryPool()
		{
			//stack에 돌아온 부분을 지운다



		}
		*/

		~CMemoryPool()
		{
			while (curNode != nullptr)
			{
				Node* nxt = curNode->NextNode;

				delete(curNode);
				curNode = nxt;
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// 블럭 하나를 할당받는다.  
		//
		// Parameters: 없음.
		// Return: (DATA *) 데이타 블럭 포인터.
		//////////////////////////////////////////////////////////////////////////
		T* Alloc(void)
		{
			Node* ret = curNode;

			if (UseCount == Capacity) __debugbreak();

			if (!ret->initial || !PlacementNew)
			{
				new (ret) T;

				ret->initial = true;
			}

			UseCount++;
			curNode = curNode->NextNode;

			return reinterpret_cast<T*>(ret);

		}

		//////////////////////////////////////////////////////////////////////////
		// 사용중이던 블럭을 해제한다.
		//
		// Parameters: (DATA *) 블럭 포인터.
		// Return: (BOOL) TRUE, FALSE.
		//////////////////////////////////////////////////////////////////////////
		bool Free(T* pData)
		{
			Node* input = reinterpret_cast<Node*>(pData);
		//	printf("%d %d\n", (Node*)input->Data,(T*)input);

			//placement new면 소멸자 호출여부
			if (!PlacementNew)
			{
				pData->~T();
				input->initial = false;
			}

			input->NextNode = curNode;
			curNode = input;
			
			UseCount--;

			return true;
		}


		//////////////////////////////////////////////////////////////////////////
		// 현재 확보 된 블럭 개수를 얻는다. (메모리풀 내부의 전체 개수)
		//
		// Parameters: 없음.
		// Return: (int) 메모리 풀 내부 전체 개수
		//////////////////////////////////////////////////////////////////////////
		int		GetCapacityCount(void) { return Capacity; }

		//////////////////////////////////////////////////////////////////////////
		// 현재 사용중인 블럭 개수를 얻는다.
		//
		// Parameters: 없음.
		// Return: (int) 사용중인 블럭 개수.
		//////////////////////////////////////////////////////////////////////////
		int		GetUseCount(void) { return UseCount; }


		// 스택 방식으로 반환된 (미사용) 오브젝트 블럭을 관리.


	};

}





















#endif