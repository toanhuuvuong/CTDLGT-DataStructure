#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include<iostream>
#include<vector>

#define M 11

// Hàm hash
int hashCode(const int &key)
{
	return (key % M);
}
// Tạo Node
template<typename T>
struct NODE
{
	int key;
	T data;
};
// Lấy Node
template<typename T>
NODE<T>* getNode(const int &key, const T &data)
{
	return new NODE<T>{ key, data };
}
// Khởi tạo
template<typename T>
void init(NODE<T>* hashTable[M])
{
	for (int i = 0; i < M; i++)
		hashTable[i] = NULL;
}
// Thêm Node
template<typename T>
void addNode(const int &key, const T &data, NODE<T>* hashTable[M])
{
	NODE<T>* cur = getNode(key, data);
	int indexHashTable = hashCode(key);

	while (hashTable[indexHashTable] != NULL)
	{
		indexHashTable++;
		indexHashTable %= M;
	}
	hashTable[indexHashTable] = cur;
}
// Tìm Node
template<typename T>
NODE<T>* searchNode(const int &key, NODE<T>* hashTable[M])
{
	int indexHashTable = hashCode(key);

	while (hashTable[indexHashTable] != NULL && hashTable[indexHashTable]->key != key)
	{
		indexHashTable++;
		indexHashTable %= M;
	}
	return hashTable[indexHashTable];
}
// Xoá Node
template<typename T>
void deleteNode(const int &key, NODE<T>* hashTable[M])
{

	NODE<T>* cur = searchNode(key, hashTable);
	if (cur)
		delete cur;
}
// Hủy hash table
template<typename T>
void destroyHashTable(NODE<T>* hashTable[M])
{
	for (int i = 0; i < M; i++)
	{
		if (hashTable[i] != NULL)
			deleteNode(hashTable[i]->key, hashTable);
	}
}
#endif

