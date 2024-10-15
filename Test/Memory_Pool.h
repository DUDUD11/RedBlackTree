#pragma once

#ifndef  __PROCADEMY_MEMORY_POOL__
#define  __PROCADEMY_MEMORY_POOL__
#include <new.h>

/*---------------------------------------------------------------

	procademy MemoryPool.

	�޸� Ǯ Ŭ���� (������Ʈ Ǯ / ��������Ʈ)
	Ư�� ����Ÿ(����ü,Ŭ����,����)�� ������ �Ҵ� �� ��������.

	- ����.

	procademy::CMemoryPool<DATA> MemPool(300, FALSE);
	DATA *pData = MemPool.Alloc();

	pData ���

	MemPool.Free(pData);

	// placement new �̸� node �޺κп� �ʱ�ȭ���θ� �ִ´�.
----------------------------------------------------------------*/

namespace MemoryPool
{

	template <class T>
	class CMemoryPool
	{
		struct Node
		{
			T Data; //data�� �������ҵ�
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

		// ���ÿ� ������ wrapper�� ���μ� �ڽ��� T���� Ȯ���ϴ� ���� �־ ����
	public:

		//////////////////////////////////////////////////////////////////////////
		// ������, �ı���.
		//
		// Parameters:	(int) �ʱ� �� ����.
		//				(bool) Alloc �� ������ / Free �� �ı��� ȣ�� ����
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
			//stack�� ���ƿ� �κ��� �����



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
		// �� �ϳ��� �Ҵ�޴´�.  
		//
		// Parameters: ����.
		// Return: (DATA *) ����Ÿ �� ������.
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
		// ������̴� ���� �����Ѵ�.
		//
		// Parameters: (DATA *) �� ������.
		// Return: (BOOL) TRUE, FALSE.
		//////////////////////////////////////////////////////////////////////////
		bool Free(T* pData)
		{
			Node* input = reinterpret_cast<Node*>(pData);
		//	printf("%d %d\n", (Node*)input->Data,(T*)input);

			//placement new�� �Ҹ��� ȣ�⿩��
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
		// ���� Ȯ�� �� �� ������ ��´�. (�޸�Ǯ ������ ��ü ����)
		//
		// Parameters: ����.
		// Return: (int) �޸� Ǯ ���� ��ü ����
		//////////////////////////////////////////////////////////////////////////
		int		GetCapacityCount(void) { return Capacity; }

		//////////////////////////////////////////////////////////////////////////
		// ���� ������� �� ������ ��´�.
		//
		// Parameters: ����.
		// Return: (int) ������� �� ����.
		//////////////////////////////////////////////////////////////////////////
		int		GetUseCount(void) { return UseCount; }


		// ���� ������� ��ȯ�� (�̻��) ������Ʈ ���� ����.


	};

}





















#endif