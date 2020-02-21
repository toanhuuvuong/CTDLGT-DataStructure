#ifndef __AA_TREE_H__
#define __AA_TREE_H__

#include<iostream>

template<class T>
class NODE
{
public:
	int m_key;
	T m_data;
	int m_level;
	NODE<T> *m_pLeft, *m_pRight;

	NODE(const int &key, const T &data) : m_key(key), m_data(data) 
	{
		m_level = 1;
		m_pLeft = m_pRight = NULL;
	}

	bool isLeftHorizontal() { return (m_pLeft && m_level == m_pLeft->m_level); }
	bool isRightHorizontal() { return (m_pRight && m_level == m_pRight->m_level); }
};
template<class T>
class AA_TREE
{
private:
	void split(NODE<T>* &P)
	{
		if (P == NULL || P->m_pRight == NULL)
			return;
		NODE<T>* Q = P->m_pRight; 
		bool isRoot = (P == m_pRoot);
		// Bẻ liên kết 1
		P->m_pRight = Q->m_pLeft;
		// Bẻ liên kết 2
		Q->m_pLeft = P;
		// Tăng mức
		Q->m_level++;
		// Đổi gốc
		P = Q;
		// Cập nhật gốc cây
		if (isRoot)
			m_pRoot = P;
	}
	void skew(NODE<T>* &P)
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
		// Cập nhật gốc cây
		if (isRoot)
			m_pRoot = P;
	}
	void swapValue(NODE<T>* a, NODE<T>* b)
	{
		int tempKey = a->m_key;
		a->m_key = b->m_key;
		b->m_key = tempKey;

		T tempData = a->m_data;
		a->m_data = b->m_data;
		b->m_data = tempData;
	}
	void readjusted(NODE<T>* &P)
	{
		if (P == NULL)
			return;
		// Skew 3 lần, Split 2 lần
		if (P->isLeftHorizontal())
		{
			// Liên kết ngang trái
			skew(P);
			if (P->m_pRight && P->m_pRight->isLeftHorizontal())
			{
				skew(P->m_pRight);
				if (P->m_pRight->m_pRight && P->m_pRight->m_pRight->isLeftHorizontal())
					skew(P->m_pRight->m_pRight);
			}
		}
		if (P->isRightHorizontal() && P->m_pRight && P->m_pRight->isRightHorizontal())
		{
			// Hai liên kết ngang phải liên tiếp
			split(P);
			if (P->m_pRight->isRightHorizontal() && P->m_pRight->m_pRight && P->m_pRight->m_pRight->isRightHorizontal())
				split(P->m_pRight);
		}
	}
	void addNode(NODE<T>* &pRoot, NODE<T>* newNode)
	{
		if (pRoot == NULL)
		{
			pRoot = newNode;
			return;
		}

		if (newNode->m_key < pRoot->m_key)
			addNode(pRoot->m_pLeft, newNode);
		else if (newNode->m_key > pRoot->m_key)
			addNode(pRoot->m_pRight, newNode);
		else
			return;
		readjusted(pRoot);
	}
	void deleteNode(NODE<T>* &pRoot, NODE<T>* &V)
	{
		if (pRoot == NULL || V == NULL)
			return;

		if (pRoot->m_key == V->m_key)
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
				NODE<T>** pHeir = &(pRoot->m_pRight);
				while ((*pHeir)->m_pLeft)
					pHeir = &((*pHeir)->m_pLeft);
				// Copy dữ liệu
				swapValue(pRoot, (*pHeir));
				// Xóa node đơn
				temp = *pHeir;
				*pHeir = (*pHeir)->m_pRight;
			}
			delete temp;
		}
		else if (pRoot->m_key > V->m_key)
			deleteNode(pRoot->m_pLeft, V);
		else
			deleteNode(pRoot->m_pRight, V);

		readjusted(pRoot);
	}
public:
	NODE<T>* m_pRoot;

	AA_TREE() { m_pRoot = NULL; }

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
		addNode(m_pRoot, newNode);
	}
	void deleteNodeByValue(const int &key)
	{
		NODE<T>* V = searchNodeByValue(key);
		deleteNode(m_pRoot, V);
	}
};

#endif