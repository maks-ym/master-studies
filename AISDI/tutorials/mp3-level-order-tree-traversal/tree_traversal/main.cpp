/**
 * Copyright (C) 2016-12-07 Maks-ym (hereafter "Author")
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the Author shall not be used in advertising or
 * otherwise to promote the sale, use or other dealings in this Software without prior written
 * authorization from the Author.
 */

/**
 * tree level order traversal using printLevel function
 */

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
