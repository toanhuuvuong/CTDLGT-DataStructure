#ifndef __RED_BLACK_TREE__
#define __RED_BLACK_TREE__

#include<iostream>
#include<vector>
#include<iomanip>
#include<minmax.h>

#define LENGTH_NUMBER 4

enum COLOR{ RED, BLACK };

template<class T>
class NODE
{
public:
	int m_key;
	T m_data;
	COLOR m_color;
	NODE<T> *m_pLeft, *m_pRight, *m_pParent;

	NODE(const int &key, const T &data) : m_key(key), m_data(data)
	{
		m_color = RED;
		m_pLeft = m_pRight = m_pParent = NULL;
	}

	bool isOnLeft() { return (m_pParent && m_pParent->m_pLeft == this); }
	bool hasRedChild() { return ((m_pLeft && m_pLeft->m_color == RED) || (m_pRight && m_pRight->m_color == RED)); }

	NODE<T>* sibling()
	{
		if (m_pParent == NULL)
			return NULL;
		if (isOnLeft())
			return m_pParent->m_pRight;
		return m_pParent->m_pLeft;
	}
	NODE<T>* uncle()
	{
		// Nếu không có cha hoặc không có ông thì không có chú
		if (m_pParent == NULL || m_pParent->m_pParent == NULL)
			return NULL;
		// Chú nằm bên phải cha
		if (m_pParent->isOnLeft())
			return m_pParent->m_pParent->m_pRight;
		// Chú nằm bên trái cha
		return m_pParent->m_pParent->m_pLeft;
	}
	NODE<T>* successor()
	{
		if (m_pLeft == NULL && m_pRight == NULL)
			return NULL; // Khi node là lá
		if (m_pLeft && m_pRight == NULL)
			return m_pLeft; // Khi node có 1 con trái
		if (m_pLeft == NULL && m_pRight)
			return m_pRight; // Khi node có 1 con phải
		// Khi node có 2 con
		NODE<T>* pCur = m_pLeft;
		while (pCur->m_pRight)
			pCur = pCur->m_pRight;
		return pCur;
	}
};
template<class T>
class RED_BLACK_TREE
{
private:
	void leftRotation(NODE<T>* &P)
	{
		if (P == NULL || P->m_pRight == NULL)
			return;
		NODE<T>* Q = P->m_pRight;
		// Cập nhật lại gốc cây
		if (P == m_pRoot)
			m_pRoot = Q;
		// Bẻ liên kết 1
		if (P->m_pParent)
		{
			if (P->isOnLeft())
				P->m_pParent->m_pLeft = Q;
			else
				P->m_pParent->m_pRight = Q;
		}
		Q->m_pParent = P->m_pParent;
		// Bẻ liên kết 2
		if (Q->m_pLeft)
			Q->m_pLeft->m_pParent = P;
		P->m_pRight = Q->m_pLeft;
		// Bẻ liên kết 3
		P->m_pParent = Q;
		Q->m_pLeft = P;
		// Đổi gốc
		P = Q;
	}
	void rightRotation(NODE<T>* &P)
	{
		if (P == NULL || P->m_pLeft == NULL)
			return;
		NODE<T>* Q = P->m_pLeft;
		// Cập nhật lại gốc cây
		if (P == m_pRoot)
			m_pRoot = Q;
		// Bẻ liên kết 1
		if (P->m_pParent)
		{
			if (P->isOnLeft())
				P->m_pParent->m_pLeft = Q;
			else
				P->m_pParent->m_pRight = Q;
		}
		Q->m_pParent = P->m_pParent;
		// Bẻ liên kết 2
		if (Q->m_pRight)
			Q->m_pRight->m_pParent = P;
		P->m_pLeft = Q->m_pRight;
		// Bẻ liên kết 3
		P->m_pParent = Q;
		Q->m_pRight = P;
		// Đổi gốc
		P = Q;
	}
	void swapColor(NODE<T>* a, NODE<T>* b)
	{
		if (a == NULL || b == NULL)
			return;

		COLOR temp = a->m_color;
		a->m_color = b->m_color;
		b->m_color = temp;
	}
	void swapValue(NODE<T>* a, NODE<T>* b)
	{
		if (a == NULL || b == NULL)
			return;

		int tempKey = a->m_key;
		a->m_key = b->m_key;
		b->m_key = tempKey;

		T tempData = a->m_data;
		a->m_data = b->m_data;
		b->m_data = tempData;
	}
	void fixRedRed(NODE<T>* &P)
	{
		if (P == NULL || P->m_color == BLACK)
			return;
		// Mặc định gặp node gốc phải là màu đen
		if (P == m_pRoot)
		{
			P->m_color = BLACK;
			return;
		}
		// Điều chỉnh xung đột đỏ - đỏ
		NODE<T> *pParent = P->m_pParent, *pGrandParent = P->m_pParent->m_pParent, *pUncle = P->uncle();
		if (pParent->m_color == RED)
		{
			if (pUncle && pUncle->m_color == RED)
			{
				// TH1 và TH1'
				pGrandParent->m_color = RED;
				pParent->m_color = pUncle->m_color = BLACK;
				// Xử lí xung đột đỏ - đỏ từ node ông trở lên node gốc (nếu có)
				fixRedRed(pGrandParent);
			}
			else
			{
				if (pParent->isOnLeft())
				{
					// TH2 và TH3
					if (P->isOnLeft() == false)
						leftRotation(pParent);
					swapColor(pParent, pGrandParent);
					rightRotation(pGrandParent);
				}
				else
				{
					// TH2' và TH3'
					if (P->isOnLeft())
						rightRotation(pParent);
					swapColor(pParent, pGrandParent);
					leftRotation(pGrandParent);
				}
			}
		}
	}
	void fixDoubleBlack(NODE<T>* &U)
	{
		if (U == m_pRoot)
			return;
		NODE<T> *S = U->sibling(), *P = U->m_pParent;

		if (S == NULL) 
			fixDoubleBlack(P); // Double Black bị đẩy lên node ông
		else if (S->m_color == BLACK)
		{
			// S có màu đen
			if (S->hasRedChild()) // TH1--------------------------------------------------------
			{
				// S có ít nhất 1 con đỏ
				NODE<T>* R = (S->m_pLeft && S->m_pLeft->m_color == RED) ? S->m_pLeft : S->m_pRight;
				if (S->isOnLeft())
				{
					if (R->isOnLeft())
					{
						// LL
						R->m_color = S->m_color;
						S->m_color = P->m_color;
						P->m_color = BLACK;
						rightRotation(P);
					}
					else
					{
						// LR
						R->m_color = P->m_color;
						P->m_color = BLACK;
						leftRotation(S);
						rightRotation(P);
					}
				}
				else
				{
					if (R->isOnLeft())
					{
						// RL
						R->m_color = P->m_color;
						P->m_color = BLACK;
						rightRotation(S);
						leftRotation(P);
					}
					else
					{
						// RR
						R->m_color = BLACK;
						S->m_color = P->m_color;
						P->m_color = BLACK;
						leftRotation(P);
					}
				}
			}
			else // TH2--------------------------------------------------------
			{
				// S có 2 con đều là đen
				S->m_color = RED;
				(P->m_color == RED) ? P->m_color = BLACK : fixDoubleBlack(P);
			}
		}
		else // TH3--------------------------------------------------------
		{
			// S có màu đỏ
			swapColor(P, S);
			(S->isOnLeft()) ? rightRotation(P) : leftRotation(P);
			// fix xong TH3 sẽ dẫn đến (TH1 hoặc TH2)
			fixDoubleBlack(U);
		}
	}
	void deleteNode(NODE<T>* &V)
	{
		if (V == NULL)
			return;

		NODE<T> *U = V->successor(), *P = V->m_pParent;
		bool areUVBlack = ((U == NULL || U->m_color == BLACK) && (V->m_color == BLACK));

		if (V->m_pLeft == NULL && V->m_pRight == NULL) 	// V là lá (U = NULL)
		{
			if (V == m_pRoot)
				m_pRoot = NULL;
			else
			{
				if (areUVBlack) // V màu đen thì xảy ra DoubleBlack (còn V màu đỏ thì không làm gì)
					fixDoubleBlack(V);
				else
				{
					if (V->sibling())
						V->sibling()->m_color = RED;
				}
				(V->isOnLeft()) ? P->m_pLeft = NULL : P->m_pRight = NULL;
			}
			delete V;
		}
		else if (V->m_pLeft != NULL && V->m_pRight != NULL) // V có 2 con
		{
			swapValue(V, U);
			deleteNode(U);
		}
		else // V có 1 con
		{
			if (V == m_pRoot)
			{
				swapValue(U, m_pRoot);
				m_pRoot->m_pLeft = m_pRoot->m_pRight = NULL;
				delete U;
			}
			else
			{
				(V->isOnLeft()) ? P->m_pLeft = U : P->m_pRight = U;
				U->m_pParent = P;
				delete V;
				if (areUVBlack)
					fixDoubleBlack(U);
				else
					U->m_color = BLACK;
			}
		}
	}

	int S(const int &h)
	{
		// khoảng cách từ mép trái CMD đến node đầu tiên trên cùng 1 depth
		if (h < 1)
			return -1;
		return ((h == 1) ? 1 : pow(2, h - 2) * (1 + LENGTH_NUMBER));
	}
	int A(const int &h)
	{
		// khoảng cách giữa 2 cặp node cùng depth
		if (h < 1)
			return -1;
		if (h == 1)
			return 1;
		return (pow(2, h - 1) * (LENGTH_NUMBER + 1) - 1);
	}
	int B(const int &h)
	{
		// khoảng cách giữa 2 node con cùng cha
		if (h < 1)
			return -1;
		if (h == 1)
			return 1;
		return A(h - 1) + B(h - 1) + 1;
	}
	int L(const int &h)
	{
		// khoảng cách đường liên kết node cha và 2 node con
		if (h < 2)
			return -1;
		return (2 * LENGTH_NUMBER + B(h - 1));
	}
	void printConsecutiveSpace(const int &length)
	{
		for (int i = 0; i < length; i++)
			std::cout << ' ';
	}
	void printKeyNode(const int &key, const bool &isOnLeft)
	{
		if (key != -1)
		{
			if (isOnLeft)
				std::cout << std::setw(LENGTH_NUMBER) << std::left << key;
			else
				std::cout << std::setw(LENGTH_NUMBER) << std::right << key;
		}
		else
		{
			if (isOnLeft)
				std::cout << std::setw(LENGTH_NUMBER) << std::left << "NULL";
			else
				std::cout << std::setw(LENGTH_NUMBER) << std::right << "NULL";
		}
	}
	void printConnectivePath(const int &length)
	{
		int i, mid = length / 2 + 1;
		for (i = 1; i < mid; i++)
			std::cout << '_';
		std::cout << '|';
		for (i = mid + 1; i <= length; i++)
			std::cout << '_';
	}
	void printListKeyEqualDepth(std::vector<int> listKey, const int &h)
	{
		int i, size = listKey.size();
		std::vector<int> listPrev;
		listKeyEqualDepth(m_pRoot, listPrev, height(m_pRoot) - h - 1);
		// in Sh
		printConsecutiveSpace(S(h));
		// in key 1 và key 2 (nếu có)
		if (height(m_pRoot) == h)
		{
			printKeyNode(listKey[0], true);
			return;
		}
		if (listPrev[0] != -1)
		{
			printKeyNode(listKey[0], true);
			if (size > 1)
			{
				printConsecutiveSpace(B(h));
				printKeyNode(listKey[1], false);
			}
		}
		else
			printConsecutiveSpace(2 * LENGTH_NUMBER + B(h));
		// in từ key 3 trở lên
		for (i = 2; i < size; i += 2)
		{
			printConsecutiveSpace(A(h));
			if (listPrev[i / 2] != -1)
			{
				printKeyNode(listKey[i], true);
				printConsecutiveSpace(B(h));
				printKeyNode(listKey[i + 1], false);
			}
			else
				printConsecutiveSpace(2 * LENGTH_NUMBER + B(h));
		}
	}
	void listKeyEqualDepth(NODE<T>* pRoot, std::vector<int> &listKey, const int &d)
	{
		if (pRoot == NULL || d >= height(m_pRoot) || d < 0 || depth(pRoot) > d)
			return;

		listKeyEqualDepth(pRoot->m_pLeft, listKey, d);

		int dNode = depth(pRoot), numberNull = 0;
		if (dNode == d)
			listKey.push_back(pRoot->m_key);
		else
		{
			if (pRoot->m_pLeft == NULL)
			{
				numberNull = pow(2, d - dNode - 1);
				while (numberNull--)
					listKey.push_back(-1);
			}
			if (pRoot->m_pRight == NULL)
			{
				numberNull = pow(2, d - dNode - 1);
				while (numberNull--)
					listKey.push_back(-1);
			}
		}

		listKeyEqualDepth(pRoot->m_pRight, listKey, d);
	}
public:
	NODE<T>* m_pRoot;

	RED_BLACK_TREE() { m_pRoot = NULL; }

	NODE<T>* searchNodeByValue(const int &key)
	{
		NODE<T> *pCur = m_pRoot;
		while (pCur)
		{
			if (key < pCur->m_key)
				pCur = pCur->m_pLeft;
			else if (key > pCur->m_key)
				pCur = pCur->m_pRight;
			else
				return pCur;
		}
		return NULL;
	}
	void addNodeByValue(const int &key, const T &data)
	{
		NODE<T>* newNode = new NODE<T>(key, data);
		if (m_pRoot == NULL)
		{
			newNode->m_color = BLACK;
			m_pRoot = newNode;
		}
		else
		{
			NODE<T> *pCur = m_pRoot;
			while (pCur)
			{
				if (key < pCur->m_key)
				{
					if (pCur->m_pLeft == NULL)
						break;
					pCur = pCur->m_pLeft;
				}
				else if (key > pCur->m_key)
				{
					if (pCur->m_pRight == NULL)
						break;
					pCur = pCur->m_pRight;
				}
				else
					return;
			}
			newNode->m_pParent = pCur;
			(key < pCur->m_key) ? pCur->m_pLeft = newNode : pCur->m_pRight = newNode;
			// Xử lí xung đột
			fixRedRed(newNode);
		}
	}
	void deleteNodeByValue(const int &key)
	{
		NODE<T>* V = searchNodeByValue(key);
		deleteNode(V);
	}
	void deleteTree()
	{
		int heightTree = height(m_pRoot), i = 0, size = 0;
		std::vector<int> listKey;

		for (i = 0; i < heightTree; i++)
			listKeyEqualDepth(m_pRoot, listKey, i);

		size = listKey.size();
		for (i = 0; i < size; i++)
			deleteNodeByValue(listKey[i]);
	}

	int height(NODE<T>* P)
	{
		if (P == NULL)
			return 0;

		if (P->m_pLeft == NULL && P->m_pRight == NULL)
			return 1;
		else if (P->m_pLeft != NULL && P->m_pRight == NULL)
			return height(P->m_pLeft) + 1;
		else if (P->m_pLeft == NULL && P->m_pRight != NULL)
			return height(P->m_pRight) + 1;
		else
			return max(height(P->m_pLeft), height(P->m_pRight)) + 1;
	}
	int depth(NODE<T>* P)
	{
		if (P == m_pRoot)
			return 0;
		return depth(P->m_pParent) + 1;
	}
	
	void drawTree()
	{
		int heightTree = height(m_pRoot);
		std::vector<int> listKey;

		for (int h = heightTree; h > 0; h--)
		{
			listKey.resize(0); // xóa bộ cũ
			listKeyEqualDepth(m_pRoot, listKey, heightTree - h); // lấy các key có cùng depth
			// in các key cùng depth
			printListKeyEqualDepth(listKey, h);
			// in các đường liên kết
			std::cout << std::endl << std::endl;
			if (h > 1)
			{
				printConsecutiveSpace(S(h - 1));
				(listKey[0] != -1) ? printConnectivePath(L(h)) : printConsecutiveSpace(L(h));
				for (int i = 1; i < listKey.size(); i++)
				{
					printConsecutiveSpace(A(h - 1));
					(listKey[i] != -1) ? printConnectivePath(L(h)) : printConsecutiveSpace(L(h));
				}
				std::cout << std::endl << std::endl;
			}

		}
	}
};

#endif