#include"AATree.h"
#include<conio.h>

int main()
{
	AA_TREE<std::string> AAT;

	AAT.addNodeByValue(4, "");
	AAT.addNodeByValue(10, "");
	AAT.addNodeByValue(2, "");
	AAT.addNodeByValue(6, "");
	AAT.addNodeByValue(12, "");
	AAT.addNodeByValue(3, "");
	AAT.addNodeByValue(1, "");
	AAT.addNodeByValue(8, "");
	AAT.addNodeByValue(13, "");
	AAT.addNodeByValue(11, "");
	AAT.addNodeByValue(5, "");
	AAT.addNodeByValue(9, "");
	AAT.addNodeByValue(7, "");

	AAT.deleteNodeByValue(4);
	AAT.deleteNodeByValue(10);
	AAT.deleteNodeByValue(2);
	AAT.deleteNodeByValue(6);
	AAT.deleteNodeByValue(12);
	AAT.deleteNodeByValue(3);
	AAT.deleteNodeByValue(1);
	AAT.deleteNodeByValue(8);
	AAT.deleteNodeByValue(13);
	AAT.deleteNodeByValue(11);
	AAT.deleteNodeByValue(5);
	AAT.deleteNodeByValue(9);
	AAT.deleteNodeByValue(7);


	_getch();
	return 0;
}