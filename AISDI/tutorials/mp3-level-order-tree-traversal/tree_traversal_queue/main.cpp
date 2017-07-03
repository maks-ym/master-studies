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
 * tree level order traversal using queue
 */

#include <iostream>
#include <queue>

//node of the tree
template <typename Type>
struct node
{
	node(Type data) : data(data), left(nullptr), right(nullptr) {};
	~node() { delete left; delete right; }
	Type data;
	struct node* left, *right;
};

//function to traverse tree level by level and print out node values
template <typename Type>
void levelTraversal(struct node<Type> & root)
{
	std::queue<node<Type>*> q;
	q.push(&root);
	while (!q.empty()) {
		node<Type>* currentNode = q.front();
		std::cout << currentNode->data << std::endl;
		if(currentNode->left)  q.push(currentNode->left);
		if(currentNode->right) q.push(currentNode->right);
		q.pop();
	}
}

//testing program
int main() {

	node<int> root(1);
	root.left  = new node<int>(2);
	root.right = new node<int>(3);
	root.left->left  = new node<int>(4);
	root.left->right = new node<int>(5);

	printf("Level Order traversal of binary tree is \n");
	levelTraversal(root);
	std::cout << std::endl;
	system("PAUSE");
	return 0;
}
