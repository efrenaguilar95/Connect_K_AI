#include "gametree.h"

int main()
{
	//Random comment
	GameTree<int> gTree(10);
	gTree.print_value();
	GameTree<int> gTree2(8);
	//GameTree<int>* g2 = &gTree2;
	gTree.addChild(gTree2);
	gTree.first_child->print_value();
	GameTree<int> gTree3(7);
	gTree.first_child->addSibling(gTree3);
	std::cout << gTree.first_child->next_sibling->value<< std::endl;

}
