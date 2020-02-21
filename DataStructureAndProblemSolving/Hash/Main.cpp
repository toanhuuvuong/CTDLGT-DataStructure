#include"HASH_TABLE.h"
#include<string>
#include<conio.h>

int main()
{
	NODE<std::string>* hashTable[M];
	init(hashTable);

	addNode<std::string>(10, "Vuong Huu Toan", hashTable);
	addNode<std::string>(22, "Ong Vinh Nhat Quang", hashTable);
	addNode<std::string>(31, "Hoang Minh Vu", hashTable);
	addNode<std::string>(4, "Tran Phuong Trinh", hashTable);
	addNode<std::string>(15, "Hua Thi Hue Huong", hashTable);
	addNode<std::string>(28, "Huynh Quoc An", hashTable);
	addNode<std::string>(17, "Ngo Nha Trang", hashTable);
	addNode<std::string>(88, "Huynh Luong Phuong Truc", hashTable);
	addNode<std::string>(59, "Tran Tuan Canh", hashTable);

	NODE<std::string>* temp = searchNode(28, hashTable);
	std::cout << temp->key << " & " << temp->data << std::endl;

	std::cout << "HASH TABLE" << std::endl;
	for (int i = 0; i < M; i++)
	{
		if (hashTable[i] != NULL)
			std::cout << hashTable[i]->key << " & " << hashTable[i]->data << std::endl;
		else
			std::cout << "NULL" << std::endl;
	}
	destroyHashTable(hashTable);

	_getch();
	return 0;
}