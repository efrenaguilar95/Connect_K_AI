#ifndef GAMETREE_H_
#define GAMETREE_H_

//Uses code by Prof. Richard Pattis for the foundation of the tree
template<class T>
class GameTree
{
	public:
		GameTree() : first_child(nullptr), next_sibling(nullptr), parent(nullptr)
		{
			//Initializes a GameTree with no children
		}

		GameTree(const GameTree<T>& n) : value(n.value), first_child(n.first_child), next_sibling(n.next_sibling), parent(n.parent)
		{
			//GameTree copy constructor
		}

		GameTree(T value, GameTree<T>* fc=nullptr, GameTree<T>* ns = nullptr, GameTree<T>* p = nullptr)
			: value(value), first_child(fc), next_sibling(ns), parent(p)
		{

		}

		T value;
		GameTree<T>* first_child;	//First for a linked list of children
		GameTree<T>* next_sibling; 	//Next in linked list of siblings
		GameTree<T>* parent;		//The parent of this node


};





#endif /* GAMETREE_H_ */
