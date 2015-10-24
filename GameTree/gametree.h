#ifndef GAMETREE_H_
#define GAMETREE_H_

#include <iostream>
//Uses code by Prof. Richard Pattis for the foundation of the tree
template<class T>
class GameTree
{
	public:
		GameTree() : first_child(NULL), next_sibling(NULL), parent(NULL)
		{
			//Initializes a GameTree with no children
		}

		GameTree(const GameTree<T>& n) : value(n.value), first_child(n.first_child), next_sibling(n.next_sibling), parent(n.parent)
		{
			//GameTree copy constructor
		}

		GameTree(T value, GameTree<T>* fc=NULL, GameTree<T>* ns = NULL, GameTree<T>* p = NULL)
			: value(value), first_child(fc), next_sibling(ns), parent(p)
		{

		}

		~GameTree()
		{
			//delete this node, and all its children (and siblings?)
		}

		T value;
		GameTree<T>* first_child;	//First for a linked list of children
		GameTree<T>* next_sibling; 	//Next in linked list of siblings
		GameTree<T>* parent;		//The parent of this node

		void print_value()
		{
			std::cout << value << std::endl;
		}



		void addChild(const GameTree<T>& child)
		{
			GameTree<T>* c = new GameTree<T>(child.value);
			first_child = c;
			first_child->parent = this;
		}

		/*void addChild(GameTree<T>* child)
		{
			first_child = child;
			first_child->parent = this;
		}
		*/

		void addSibling(const GameTree<T>& sibling)
		{
			GameTree<T>* s = new GameTree<T>(sibling.value);
			next_sibling = s;
			next_sibling->parent = parent;
		}

		void removeSiblings()
		{
			//Removes all siblings of this node, and their respective children
		}

		void dfs()
		{
			if(first_child == NULL && next_sibling == NULL)
			{
				std::cout<<value<<std::endl;
				return;
			}

			if(first_child != NULL)
			{
				dfs(first_child);
				std::cout<<value<<std::endl;
			}

			if(next_sibling!= NULL)
			{
				std::cout<<value<<std::endl;
				dfs(next_sibling);
			}
		}



		void dfs(GameTree<T>* start_node)
		{
			if(start_node->first_child == NULL && start_node->next_sibling == NULL)
			{
				std::cout<<start_node->value<<std::endl;
				return;
			}

			if(start_node->first_child != NULL)
			{
				dfs(start_node->first_child);
				std::cout<<start_node->value<<std::endl;	//This should print out after ALL the children have been reached
			}

			if(start_node->next_sibling!= NULL)
			{
				if(start_node->first_child==NULL)
					std::cout<<start_node->value<<std::endl;
				dfs(start_node->next_sibling);
			}
		}








};

template<class T>
void dfs(GameTree<T>* start_node)
		{
			if(start_node->first_child == NULL && start_node->next_sibling == NULL)
			{
				std::cout<<start_node->value<<std::endl;
				return;
			}

			if(start_node->first_child != NULL)
			{
				dfs(start_node->first_child);
			}

			std::cout<<start_node->value<<std::endl;
			if(start_node->next_sibling!= NULL)
			{
				dfs(start_node->next_sibling);
			}
		}







#endif /* GAMETREE_H_ */
