#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include<iostream>
#include<string>
#include<minmax.h>

// ===================== NODE =======================
template<class T>
class NODE
{
public:
	int m_key;
	T m_data;
	NODE<T>* m_pLeft;
	NODE<T>* m_pRight;

	NODE(const int &key, const T &data) : m_key(key), m_data(data) { m_pLeft = m_pRight = NULL; }
};
template<class T>
std::ostream& operator<<(std::ostream& outDev, NODE<T>* node)
{
	if (node)
		outDev << node->m_key << "\t-\t" << node->m_data;
	else
		outDev << "<NULL>";
	return outDev;
}
template<class T>
int height(NODE<T>* node)
{
	if (node == NULL)
		return 0;
	if (node->m_pLeft == NULL && node->m_pRight == NULL)
		return 1;
	else if (node->m_pLeft != NULL && node->m_pRight == NULL)
		return height(node->m_pLeft) + 1;
	else if (node->m_pLeft == NULL && node->m_pRight != NULL)
		return height(node->m_pRight) + 1;
	else
		return max(height(node->m_pLeft), height(node->m_pRight)) + 1;
}
// ===================== TREE =======================
template<class T>
class TREE
{
private:
	void deleteTree(NODE<T>* &pRoot)
	{
		if (pRoot)
		{
			deleteTree(pRoot->m_pLeft);
			deleteTree(pRoot->m_pRight);
			delete pRoot;
		}
	}
public:
	NODE<T>* m_pRoot;

	TREE() { m_pRoot = NULL; }
	~TREE() { 
		deleteTree(m_pRoot); 
	}
	// Thêm node
	void addNode(const int &key, const T &data)
	{
		if (m_pRoot == NULL)
		{
			m_pRoot = new NODE<T>(key, data);
			return;
		}
		NODE<T>* pAdd = m_pRoot;
		NODE<T>* pAdd_parent;
		int pAdd_key;

		while (pAdd)
		{
			pAdd_key = pAdd->m_key;
			pAdd_parent = pAdd;

			if (pAdd_key < key)
				pAdd = pAdd->m_pRight;
			else if (pAdd_key > key)
				pAdd = pAdd->m_pLeft;
			else
			{
				std::cout << key << "had existed in tree before, please change other key!!!" << std::endl;
				return;
			}
		}
		(pAdd_key < key) ? pAdd_parent->m_pRight = new NODE<T>(key, data) : pAdd_parent->m_pLeft = new NODE<T>(key, data);
	}
	// Tìm kiếm node
	NODE<T>** searchNode(const int &key)
	{
		NODE<T>** pSearch = &m_pRoot;
		int pSearch_key;

		while (*pSearch)
		{
			pSearch_key = (*pSearch)->m_key;
			if (pSearch_key < key)
				pSearch = &((*pSearch)->m_pRight);
			else if (pSearch_key > key)
				pSearch = &((*pSearch)->m_pLeft);
			else
				return pSearch;
		}
		std::cout << "Don't find " << key << std::endl;
		return NULL;
	}
	// Xóa node
	void deleteNode(const int &key)
	{
		NODE<T>** pDelete = searchNode(key);
		if (pDelete == NULL)
		{
			std::cout << key << "had existed in tree before, please change other key!!!" << std::endl;
			return;
		}
		NODE<T>* temp = *pDelete;

		if ((*pDelete)->m_pLeft == NULL && (*pDelete)->m_pRight == NULL)
			*pDelete = NULL;
		else if ((*pDelete)->m_pLeft != NULL && (*pDelete)->m_pRight == NULL)
			*pDelete = (*pDelete)->m_pLeft;
		else if ((*pDelete)->m_pLeft == NULL && (*pDelete)->m_pRight != NULL)
			*pDelete = (*pDelete)->m_pRight;
		else
		{
			NODE<T>** pHeir = &((*pDelete)->m_pRight);
			while ((*pHeir)->m_pLeft)
				pHeir = &((*pHeir)->m_pLeft);
			// Copy dữ liệu
			(*pDelete)->m_key = (*pHeir)->m_key;
			(*pDelete)->m_data = (*pHeir)->m_data;
			// Xóa node đơn
			temp = *pHeir;
			*pHeir = (*pHeir)->m_pRight;
		}
		delete temp;
	}
};
// Duyệt cây
template<class T>
void Left_Node_Right(NODE<T>* pRoot)
{
	if (pRoot)
	{
		Left_Node_Right(pRoot->m_pLeft);
		std::cout << pRoot << std::endl;
		Left_Node_Right(pRoot->m_pRight);
	}
}
#endif