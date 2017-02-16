//tree level order traversal
//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>

void printLevel( const struct node & root, int level);
int treeHeight(const struct node* node);

//node of the tree
struct node
{
	node(int data) : data(data), left(nullptr), right(nullptr) {};
	~node() { delete left; delete right; }
	int data;
	struct node* left, *right;
};

//function to traverse tree level by level and print out node values
void levelTraversal(struct node & root)
{
	int h = treeHeight(&root);
	for (int i = 0; i < h; i++)
		printLevel(root, i);
}

// print node values of the current level
void printLevel( const struct node & root, int level)
{
	if (level == 0)		std::cout << (root.data) << " ";
	else if (level > 0)	{
		if (root.left)  printLevel(*root.left,  level - 1);
		if (root.right) printLevel(*root.right, level - 1);
	}
}

// Height of the tree (the longest path)
int treeHeight(const struct node* node)
{
	int lHeight = (node->left)  ? treeHeight(node->left)  : 0;
	int rHeight = (node->right) ? treeHeight(node->right) : 0;

	if (lHeight > rHeight)
		return(lHeight + 1);
	else return(rHeight + 1);
}

//testing program
int main()
{
	node root(1);
	root.left = new node(2);
	root.right = new node(3);
	root.left->left = new node(4);
	root.left->right = new node(5);

	printf("Level Order traversal of binary tree is \n");
	levelTraversal(root);
	std::cout << std::endl;
	system("PAUSE");
	return 0;
}
