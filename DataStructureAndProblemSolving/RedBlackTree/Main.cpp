#include"RedBlackTree.h"
#include<string>
#include<conio.h>
#include<math.h>

int main()
{
	RED_BLACK_TREE<std::string> RBT;

	RBT.addNodeByValue(9, "9");
	RBT.addNodeByValue(3, "3");
	RBT.addNodeByValue(2, "2");
	RBT.addNodeByValue(7, "7");
	RBT.addNodeByValue(13, "13");
	RBT.addNodeByValue(92, "92");
	RBT.addNodeByValue(8, "8");
	RBT.addNodeByValue(100, "100");
	RBT.addNodeByValue(27, "27");
	RBT.addNodeByValue(30, "30");
	RBT.addNodeByValue(31, "31");
	RBT.addNodeByValue(99, "99");
	RBT.addNodeByValue(88, "8");

	RBT.drawTree();

	RBT.deleteTree();

	RBT.drawTree();

	_getch();
	return 0;
}

