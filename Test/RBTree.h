#pragma once
#include <stddef.h>

template <typename T>
class RBTree
{

	enum Node_Color
	{
		BLACK = 0,
		RED = 1,

	};

	struct Node
	{
		Node* pParent;
		Node* pLeft;
		Node* pRight;
		Node_Color Color;
		T data;
	};

private:

	Node Nil;
	Node* Root;
	int size;

	void remove_all(Node* node)
	{
		if (Nill(node)) return;
		remove_all(node->pLeft);
		remove_all(node->pRight);
		delete(node);

	}

public:
	RBTree()
	{
		Nil.Color = BLACK;
		Nil.pParent = NULL;
		Nil.pLeft = NULL;
		Nil.pRight = NULL;
		Root = &Nil;
		size = 0;

	}

	~RBTree()
	{
		Clear();
	}

	void Clear()
	{
		remove_all(Root);
		Root = &Nil;
		size = 0;
	}

	Node* search(Node* find, T _data)
	{
		if (Nill(find)) return NULL;

		if (find->data == _data) return find;
	
		if (_data > find->data) return search(find->pRight, _data);

		else return search(find->pLeft, _data);

	}

	Node* search_insert_parent(Node* find, int _data)
	{

		if (_data >= find->data)
		{
			if (Nill(find->pRight))
			{
				return find;
			}

			else
			{
				return search_insert_parent(find->pRight, _data);
			}
		}

		else
		{
			if (Nill(find->pLeft))
			{
				return find;
			}
			return search_insert_parent(find->pLeft, _data);
		}

	}

	Node* biggest_small(Node* node)
	{
		Node* temp = node->pLeft;
		while (!Nill(temp->pRight))
		{
			temp = temp->pRight;
		}
		return temp;
	}

	void ReBalance_Delete(Node* node) 
	{
		if (node->pParent == NULL) return;

		Node* parent = node->pParent;
		bool pleft = parent->pLeft == node;
		Node* brother = pleft ? parent->pRight : parent->pLeft;

		if (pleft) 
		{
			if (node->Color == RED)
			{
				node->Color = BLACK;
			}

			else if (brother->Color == RED)
			{
				brother->Color = BLACK;
				Left_Rotataion(parent);
				parent->Color = RED;
				ReBalance_Delete(node);

			}

			else if (brother->pLeft->Color == BLACK && brother->pRight->Color == BLACK)
			{
				brother->Color = RED;
				ReBalance_Delete(parent);

			}

			else if (brother->pRight->Color == BLACK)
			{
				brother->pLeft->Color = BLACK;
				brother->Color = RED;
				Right_Rotation(brother);
				ReBalance_Delete(node);

			}
			
			else 
			{
				brother->Color = parent->Color;
				parent->Color = BLACK;
				brother->pRight->Color = BLACK;
				Left_Rotataion(parent);
			
			}

		}

		else 
		{
			if (node->Color == RED)
			{
				node->Color = BLACK;
			}

			else if (brother->Color == RED)
			{
				brother->Color = BLACK;
				Right_Rotation(parent);
				parent->Color = RED;
				ReBalance_Delete(node);

			}

			else if (brother->pLeft->Color == BLACK && brother->pRight->Color == BLACK)
			{
				brother->Color = RED;
				ReBalance_Delete(parent);

			}

			else if (brother->pLeft->Color == BLACK)
			{
				brother->pRight->Color = BLACK;
				brother->Color = RED;
				Left_Rotataion(brother); 
				ReBalance_Delete(node);

			}
			
			else
			{
				brother->Color = parent->Color;
				parent->Color = BLACK;
				brother->pLeft->Color = BLACK;
				Right_Rotation(parent);
			}



		}
	
	}

	bool remove(int _data)
	{
		Node* node = search(Root, _data);
		Node* replace;

		if (Nill(node)) return false;

		// 왼쪽이나 오른쪽 노드가 없으면 자기자신을 지우면 된다
		if (Nill(node->pLeft) || Nill(node->pRight))  
			
		{
			Node* parent = node->pParent;

			if (!Nill(node->pLeft)) // 왼쪽만 있을때
			{

				if (Nill(parent)) // 자신이 루트이고 왼쪽노드만 있을때
				{
					node->pLeft->pParent = NULL;
					Root = node->pLeft;

					// 왼쪽을 루트로 바꾼다
				}

				else //자신이 루트가 아닐때
				{
					if (parent->pLeft == node)
					{
						parent->pLeft = node->pLeft;
						node->pLeft->pParent = parent;
					}

					else
					{
						parent->pRight = node->pLeft;
						node->pLeft->pParent = parent;			
					}

					if (node->Color == BLACK)
					{
						ReBalance_Delete(node->pLeft);
					}

					

				}


			}

			else // 오른쪽만 있을때
			{
				if (Nill(parent))
				{
					node->pRight->pParent = NULL;
					Root = node->pRight;

					// 오른쪽을 루트로 바꾼다
				}

				else //자신이 루트가 아닐때
				{
					if (parent->pLeft == node)
					{
						parent->pLeft = node->pRight;
						node->pRight->pParent = parent;
					
					}

					else 
					{
						parent->pRight = node->pRight;
						node->pRight->pParent = parent;
					}

					if (node->Color == BLACK)
					{
						ReBalance_Delete(node->pRight);
					}


				}

			}

		
			
			replace = node;
		}
		

		else
		{
			Node* replace_remove = biggest_small(node);
	
			node->data = replace_remove->data;

			replace_remove->pLeft->pParent = replace_remove->pParent;

			if(replace_remove->pParent->pLeft == replace_remove) 	replace_remove->pParent->pLeft = replace_remove->pLeft;
			else replace_remove->pParent->pRight = replace_remove->pLeft;
		


			if (replace_remove->Color == BLACK)
			{	
				ReBalance_Delete(replace_remove->pLeft);
			}


			replace = replace_remove;

		}

		Root_Color();

		size--;

		delete(replace);

		return true;
	}

	void insert(T _data)
	{
		if (size == 0)
		{
			Root = new Node();
			Root->Color = BLACK;
			Root->data = _data;
			Root->pLeft = &Nil;
			Root->pRight = &Nil;
			size++;
			return;
		}


		Node* node = new Node();
		Node* parent = search_insert_parent(Root, _data);

		node->Color = RED;
		node->data = _data;
		node->pParent = parent;
		node->pLeft = &Nil;
		node->pRight = &Nil;


		if (_data >= parent->data)
		{
			parent->pRight = node;
		}

		else
		{
			parent->pLeft = node;
		}

		ReBalance(node);

		Root_Color();

	//	Add_Nil_Node(Root);

		size++;
	}

	void Root_Color()
	{
		while (Root->pParent != NULL)
		{
			Root = Root->pParent;
		}

		if (Root->Color == RED)
		{
			Root->Color = BLACK;
		}

	}

	void ReBalance(Node* node)
	{
		// 리밸런스시 nil 노드조정
		// node 자식추가

		if (node->pParent == NULL) return;

		if (node->pParent->Color == BLACK) return;

		Node* parent = node->pParent;
		Node* grandfather = parent->pParent;
		Node* uncle = (grandfather->pLeft == parent ? grandfather->pRight : grandfather-> pLeft);

		if (parent == grandfather->pLeft)
		{
			// 나는 왼레드, 부모레드, 삼촌 블랙
			if (parent->pLeft == node && uncle->Color == BLACK)
			{
				parent->Color = BLACK;
				grandfather->Color = RED;
				Right_Rotation(grandfather);

			}

			// 나는 오른레드, 부모레드, 삼촌 블랙
			else if (parent->pRight == node && uncle->Color == BLACK)
			{
				Left_Rotataion(parent);
				ReBalance(parent);
			}

			//삼촌도 레드.
			else if (uncle->Color == RED)
			{
				parent->Color = BLACK;
				uncle->Color = BLACK;
				grandfather->Color = RED;

				ReBalance(grandfather);

			}

		}

		else
		{
			// 나는 오른레드, 부모레드, 삼촌 블랙
			if (parent->pRight == node && uncle->Color == BLACK)
			{
				parent->Color = BLACK;
				grandfather->Color = RED;
				Left_Rotataion(grandfather);

			}

			// 나는 왼레드, 부모레드, 삼촌 블랙
			else if (parent->pLeft == node && uncle->Color == BLACK)
			{
				Right_Rotation(parent);
				ReBalance(parent);
			}

			//삼촌도 레드.
			else if (uncle->Color == RED)
			{
				parent->Color = BLACK;
				uncle->Color = BLACK;
				grandfather->Color = RED;

				ReBalance(grandfather);

			}




		}



	}

	bool Nill(Node* node)
	{
		return node == NULL || node == &Nil;
	}

	void Left_Rotataion(Node* node)
	{

		if (Nill(node->pRight->pLeft))
		{
			

			Node* upper_node = node->pParent;
			Node* right_node = node->pRight;

		

			node->pParent = node->pRight;
			node->pRight = &Nil;




			right_node->pParent = upper_node;
			right_node->pLeft = node;

			if (upper_node != NULL)
			{
				bool dir = upper_node->pLeft == node;

				if (dir)
				{
					upper_node->pLeft = right_node;
				}

				else
				{
					upper_node->pRight = right_node;
				}
			}


		}

		else
		{


			Node* upper_node = node->pParent;
			Node* right_node = node->pRight;

			node->pParent = node->pRight;
			node->pRight = right_node->pLeft;



			right_node->pParent = upper_node;
			right_node->pLeft = node;



			node->pRight->pParent = node;

			if (upper_node != NULL)
			{
				bool dir = upper_node->pLeft == node;

				if (dir)
				{
					upper_node->pLeft = right_node;
				}

				else
				{
					upper_node->pRight = right_node;
				}
			}


		}

	}

	void Right_Rotation(Node* node)
	{
		if (Nill(node->pLeft->pRight))
		{


			Node* upper_node = node->pParent;
			Node* left_node = node->pLeft;

			node->pParent = node->pLeft;
			node->pLeft = &Nil;




			left_node->pParent = upper_node;
			left_node->pRight = node;

			if (upper_node != NULL)
			{
				bool dir = upper_node->pLeft == node;

				if (dir)
				{
					upper_node->pLeft = left_node;
				}

				else
				{
					upper_node->pRight = left_node;
				}
			}



		}

		else
		{


			Node* upper_node = node->pParent;
			Node* left_node = node->pLeft;

			node->pParent = node->pLeft;
			node->pLeft = left_node->pRight;


			// D 변환

			left_node->pParent = upper_node;
			left_node->pRight = node;



			//E변환

			node->pLeft->pParent = node;

			if (upper_node != NULL)
			{
				bool dir = upper_node->pLeft == node;

				if (dir)
				{
					upper_node->pLeft = left_node;
				}

				else
				{
					upper_node->pRight = left_node;
				}
			}
		}



	}

};