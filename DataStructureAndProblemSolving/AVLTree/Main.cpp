#include"AVL Tree.h"
#include<string>
#include<conio.h>

int main()
{
	AVL_TREE<std::string> AVLT;

	AVLT.addNodeByValue(1, "");
	AVLT.addNodeByValue(2, "");
	AVLT.addNodeByValue(3, "");
	AVLT.addNodeByValue(4, "");
	AVLT.addNodeByValue(5, "");
	AVLT.addNodeByValue(6, "");
	AVLT.addNodeByValue(7, "");
	AVLT.addNodeByValue(888888888, "");
	AVLT.addNodeByValue(888888887, "");
	AVLT.addNodeByValue(0, "");

	AVLT.drawTree();

	AVLT.deleteNodeByKey(4);
	AVLT.deleteNodeByKey(1000);

	AVLT.drawTree();

	_getch();
	return 0;
}
