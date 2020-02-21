#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include<iostream>
#include<iomanip>
#include<vector>
#include<minmax.h>
#include<math.h>

#define LENGTH_NUMBER 6

template<class T>
class NODE
{
public:
	int m_key;
	T m_data;
	NODE<T> *m_pLeft, *m_pRight;

	NODE(const int &key, const T &data) : m_key(key), m_data(data), m_pLeft(NULL), m_pRight(NULL) {}
	NODE<T>* parent(NODE<T>* pRoot)
	{
		NODE<T> *pCur = pRoot, *pParent = NULL;
		while (pCur)
		{
			if (m_key < pCur->m_key)
			{
				pParent = pCur;
				pCur = pCur->m_pLeft;
			}
			else if (m_key > pCur->m_key)
			{
				pParent = pCur;
				pCur = pCur->m_pRight;
			}
			else
				break;
		}
		return pParent;
	}
	~NODE() {}
};
template<class T>
class AVL_TREE
{
private:
	void leftRotation(NODE<T>* &P)
	{
		if (P == NULL || P->m_pRight == NULL)
			return;
		NODE<T>* Q = P->m_pRight;
		bool isRoot = (P == m_pRoot);
		// Bẻ liên kết 1
		P->m_pRight = Q->m_pLeft;
		// Bẻ liên kết 2
		Q->m_pLeft = P;
		// Đổi gốc
		P = Q;
		if (isRoot)
			m_pRoot = P;
	}
	void rightRotation(NODE<T>* &P)
	{
		if (P == NULL || P->m_pLeft == NULL)
			return;
		NODE<T>* Q = P->m_pLeft;
		bool isRoot = (P == m_pRoot);
		// Bẻ liên kết 1
		P->m_pLeft = Q->m_pRight;
		// Bẻ liên kết 2
		Q->m_pRight = P;
		// Đổi gốc
		P = Q;
		if (isRoot)
			m_pRoot = P;
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
		return depth(P->parent(m_pRoot)) + 1;
	}

	void rebalance(NODE<T>* &P)
	{
		if (P == NULL || abs(height(P->m_pLeft) - height(P->m_pRight)) <= 1)
			return;

		int hL = height(P->m_pLeft), hR = height(P->m_pRight);
		if (hL > hR)
		{
			int hLL = height(P->m_pLeft->m_pLeft), hLR = height(P->m_pLeft->m_pRight);
			if (hLL >= hLR)
				rightRotation(P);
			else
			{
				leftRotation(P->m_pLeft);
				rightRotation(P);
			}
		}
		else
		{
			int hRR = height(P->m_pRight->m_pRight), hRL = height(P->m_pRight->m_pLeft);
			if (hRR >= hRL)
				leftRotation(P);
			else
			{
				rightRotation(P->m_pRight);
				leftRotation(P);
			}
		}
	}
	void addNode(NODE<T>* &pRoot, NODE<T>* newNode)
	{
		if (pRoot == NULL)
		{
			pRoot = newNode;
			return;
		}
		if (pRoot->m_key == newNode->m_key)
		{
			std::cout << "Node had existed, please change the other!!!" << std::endl;
			return;
		}

		if (newNode->m_key < pRoot->m_key)
			addNode(pRoot->m_pLeft, newNode);
		else
			addNode(pRoot->m_pRight, newNode);
		rebalance(pRoot);
	}
	void deleteNode(NODE<T>* &pRoot, const int &key)
	{
		if (pRoot == NULL)
			return;

		if (pRoot->m_key == key)
		{
			NODE<T>* temp = pRoot;

			if (pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL)
				pRoot = NULL;
			else if (pRoot->m_pLeft != NULL && pRoot->m_pRight == NULL)
				pRoot = pRoot->m_pLeft;
			else if (pRoot->m_pLeft == NULL && pRoot->m_pRight != NULL)
				pRoot = pRoot->m_pRight;
			else
			{
				NODE<T>** pHeir = &(pRoot->m_pLeft);
				while ((*pHeir)->m_pRight)
					pHeir = &((*pHeir)->m_pRight);
				// Copy dữ liệu
				swapValue(pRoot, *pHeir);
				// Xóa node đơn
				temp = *pHeir;
				*pHeir = (*pHeir)->m_pLeft;
			}
			delete temp;
		}
		else if (pRoot->m_key > key)
			deleteNode(pRoot->m_pLeft, key);
		else
			deleteNode(pRoot->m_pRight, key);
		rebalance(pRoot);
	}
	void deleteTree(NODE<T>* &P)
	{
		if (P)
		{
			deleteTree(P->m_pLeft);
			deleteTree(P->m_pRight);
			delete P; P = NULL;
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
	void displayConsecutiveSpace(const int &length)
	{
		for (int i = 0; i < length; i++)
			std::cout << ' ';
	}
	void displayKeyNode(const int &key, const bool &isOnLeft)
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
	void displayConnectivePath(const int &length)
	{
		int i, mid = length / 2 + 1;
		for (i = 1; i < mid; i++)
			std::cout << '_';
		std::cout << '|';
		for (i = mid + 1; i <= length; i++)
			std::cout << '_';
	}
	void displayListKeyEqualDepth(std::vector<int> listKey, const int &h)
	{
		int i, size = listKey.size();
		std::vector<int> listPrev;
		listKeyEqualDepth(m_pRoot, listPrev, height(m_pRoot) - h - 1);
		// in Sh
		displayConsecutiveSpace(S(h));
		// in key 1 và key 2 (nếu có)
		if (height(m_pRoot) == h)
		{
			displayKeyNode(listKey[0], true);
			return;
		}
		if (listPrev[0] != -1)
		{
			displayKeyNode(listKey[0], true);
			if (size > 1)
			{
				displayConsecutiveSpace(B(h));
				displayKeyNode(listKey[1], false);
			}
		}
		else
			displayConsecutiveSpace(2 * LENGTH_NUMBER + B(h));
		// in từ key 3 trở lên
		for (i = 2; i < size; i += 2)
		{
			displayConsecutiveSpace(A(h));
			if (listPrev[i / 2] != -1)
			{
				displayKeyNode(listKey[i], true);
				displayConsecutiveSpace(B(h));
				displayKeyNode(listKey[i + 1], false);
			}
			else
				displayConsecutiveSpace(2 * LENGTH_NUMBER + B(h));
		}
	}
	void listKeyEqualDepth(NODE<T>* P, std::vector<int> &listKey, const int &d)
	{
		if (P == NULL || d >= height(m_pRoot) || d < 0 || depth(P) > d)
			return;
		listKeyEqualDepth(P->m_pLeft, listKey, d);
		int dNode = depth(P), numberNull = 0;
		if (dNode == d)
			listKey.push_back(P->m_key);
		else
		{
			if (P->m_pLeft == NULL)
			{
				numberNull = pow(2, d - dNode - 1);
				while (numberNull--)
					listKey.push_back(-1);
			}
			if (P->m_pRight == NULL)
			{
				numberNull = pow(2, d - dNode - 1);
				while (numberNull--)
					listKey.push_back(-1);
			}
		}
		listKeyEqualDepth(P->m_pRight, listKey, d);
	}
public:
	NODE<T>* m_pRoot;

	AVL_TREE() { m_pRoot = NULL; }
	NODE<T>* searchNodeByKey(const int &key)
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
		addNode(m_pRoot, newNode);
	}
	void deleteNodeByKey(const int &key)
	{
		deleteNode(m_pRoot, key);
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
			displayListKeyEqualDepth(listKey, h);
			// in các đường liên kết
			std::cout << std::endl << std::endl;
			if (h > 1)
			{
				displayConsecutiveSpace(S(h - 1));
				(listKey[0] != -1) ? displayConnectivePath(L(h)) : displayConsecutiveSpace(L(h));
				for (int i = 1; i < listKey.size(); i++)
				{
					displayConsecutiveSpace(A(h - 1));
					(listKey[i] != -1) ? displayConnectivePath(L(h)) : displayConsecutiveSpace(L(h));
				}
				std::cout << std::endl << std::endl;
			}
		}
	}
	~AVL_TREE() 
	{
		deleteTree(m_pRoot);
	}
};
#endif

//#ifndef AVL_TREE_H
//#define AVL_TREE_H
//
//#include<iostream>
//#include<string>
//#include<minmax.h>
//
//#define LeftLeaning -1
//#define Equal 0
//#define RightLeaning 1
//
//// ================ ĐỊNH NGHĨA DỮ LIỆU ==================
//template<class T>
//struct INFO
//{
//	int key;
//	T data;
//};
//template<class T>
//struct NODE
//{
//	INFO<T> m_info;
//	NODE<T>* m_pLeft;
//	NODE<T>* m_pRight;
//	int m_balance;
//};
//// ================ KHỞI TẠO ===================
//template<class T>
//void initialization(NODE<T>* &pRoot) { pRoot = NULL; }
//// =============== LẤY NODE ====================
//template<class T>
//NODE<T>* getNode(const INFO<T> &info)
//{
//	return new NODE<T>{ info, NULL, NULL, Equal };
//}
//// =============== XUẤT NODE ===================
//template<class T>
//std::ostream& operator<<(std::ostream &outDev, NODE<T>* pNode)
//{
//	outDev << pNode->m_info.key << "\t-\t" << pNode->m_info.data;
//	return outDev;
//}
//// =============== CHIỀU CAO ===================
//template<class T>
//int height(NODE<T>* pNode)
//{
//	if (pNode == NULL)
//		return 0;
//
//	if (pNode->m_pLeft == NULL && pNode->m_pRight == NULL)
//		return 1;
//	else if (pNode->m_pLeft != NULL && pNode->m_pRight == NULL)
//		return height(pNode->m_pLeft) + 1;
//	else if (pNode->m_pLeft == NULL && pNode->m_pRight != NULL)
//		return height(pNode->m_pRight) + 1;
//	else
//		return max(height(pNode->m_pLeft), height(pNode->m_pRight)) + 1;
//}
//// ============== HỆ SỐ CÂN BẰNG ================
//template<class T>
//int balance(NODE<T>* &pNode)
//{
//	return height(pNode->m_pRight) - height(pNode->m_pLeft);
//}
//// ================ TÁI CÂN BẰNG ================
//template<class T>
//void left_rotation(NODE<T>* &P)
//{
//	if (P == NULL || P->m_pRight == NULL)
//		return;
//	NODE<T>* Q = P->m_pRight;
//	P->m_pRight = Q->m_pLeft;
//	Q->m_pLeft = P;
//	P = Q;
//}
//template<class T>
//void right_rotation(NODE<T>* &P)
//{
//	if (P == NULL || P->m_pLeft == NULL)
//		return;
//	NODE<T>* Q = P->m_pLeft;
//	P->m_pLeft = Q->m_pRight;
//	Q->m_pRight = P;
//	P = Q;
//}
//template<class T>
//void rebalance(NODE<T>* &pNode)
//{
//	if (pNode == NULL || (pNode->m_pLeft == NULL && pNode->m_pRight == NULL) || abs(height(pNode->m_pLeft) - height(pNode->m_pRight)) <= 1)
//		return;
//
//	int hL = height(pNode->m_pLeft), hR = height(pNode->m_pRight);
//	if (hL > hR)
//	{ 
//		int hLL = height(pNode->m_pLeft->m_pLeft), hLR = height(pNode->m_pLeft->m_pRight);
//		if (hLL > hLR)
//			right_rotation(pNode);
//		else
//		{
//			left_rotation(pNode->m_pLeft);
//			right_rotation(pNode);
//		}
//	}
//	else
//	{
//		int hRR = height(pNode->m_pRight->m_pRight), hRL = height(pNode->m_pRight->m_pLeft);
//		if (hRR > hRL)
//			left_rotation(pNode);
//		else
//		{
//			right_rotation(pNode->m_pRight);
//			left_rotation(pNode);
//		}
//	}
//}
//template<class T>
//void addNode(NODE<T>* &pRoot, const INFO<std::string> &info)
//{
//	if (pRoot == NULL)
//	{
//		pRoot = getNode(info);
//		return;
//	}
//	if (pRoot->m_info.key == info.key)
//	{
//		std::cout << "Info had existed, please change the other!!!" << std::endl;
//		return;
//	}
//
//	if (pRoot->m_info.key > info.key)
//	{
//		addNode(pRoot->m_pLeft, info);
//		rebalance(pRoot);
//	}
//	else
//	{
//		addNode(pRoot->m_pRight, info);
//		rebalance(pRoot);
//	}
//}
//template<class T>
//NODE<T>** searchNode(const int &key)
//{
//	NODE<T>** pSearch = &m_pRoot;
//	int pSearch_key;
//
//	while (*pSearch)
//	{
//		pSearch_key = (*pSearch)->m_key;
//		if (pSearch_key < key)
//			pSearch = &((*pSearch)->m_pRight);
//		else if (pSearch_key > key)
//			pSearch = &((*pSearch)->m_pLeft);
//		else
//			return pSearch;
//	}
//	std::cout << "Don't find " << key << std::endl;
//	return NULL;
//}
//template<class T>
//void deleteNode(NODE<T>* &pRoot, const int &key)
//{
//	if (pRoot == NULL)
//		return;
//
//	if (pRoot->m_info.key == key)
//	{
//		NODE<T>* temp = pRoot;
//
//		if (pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL)
//			pRoot = NULL;
//		else if (pRoot->m_pLeft != NULL && pRoot->m_pRight == NULL)
//			pRoot = pRoot->m_pLeft;
//		else if (pRoot->m_pLeft == NULL && pRoot->m_pRight != NULL)
//			pRoot = pRoot->m_pRight;
//		else
//		{
//			NODE<T>** pHeir = &(pRoot->m_pRight);
//			while ((*pHeir)->m_pLeft)
//				pHeir = &((*pHeir)->m_pLeft);
//			// Copy dữ liệu
//			pRoot->m_info = (*pHeir)->m_info;
//			// Xóa node đơn
//			temp = *pHeir;
//			*pHeir = (*pHeir)->m_pRight;
//		}
//		delete temp;
//	}
//	else if (pRoot->m_info.key > key)
//		deleteNode(pRoot->m_pLeft, key);
//	else
//		deleteNode(pRoot->m_pRight, key);
//	rebalance(pRoot);
//}
//template<class T>
//void deleteTree(NODE<T>* &pRoot)
//{
//	if (pRoot)
//	{
//		deleteTree(pRoot->m_pLeft);
//		deleteTree(pRoot->m_pRight);
//		deleteNode(pRoot, pRoot->m_info.key);
//	}
//}
//#endif
