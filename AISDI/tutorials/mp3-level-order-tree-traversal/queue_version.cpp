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
