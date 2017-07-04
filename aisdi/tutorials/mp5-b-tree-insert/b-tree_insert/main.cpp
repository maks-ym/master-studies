/**
 * Copyright (C) 2017-01-18 Maks-ym (hereafter "Author")
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
  * B-tree insert function
  */

#include<stdio.h>
#include<conio.h>
#include<iostream>

using namespace std;

struct Node
{
	int *data;
	Node **child_ptr;
	bool leaf;
	int n;

	Node() {
		int i;
		data = new int[5];
		child_ptr = new Node *[6];
		leaf = true;
		n = 0;
		for (i = 0; i < 6; i++) {
			child_ptr[i] = NULL;
		}
	}
}
*root = NULL, *np = NULL, *x = NULL;

void traverse(Node *p)
{
	if (p == nullptr) {
		return;
	}
	cout << endl;
	int i;
	for (i = 0; i < p->n; i++)	{
		if (p->leaf == false)		{
			traverse(p->child_ptr[i]);
		}
		cout << " " << p->data[i];
	}
	if (p->leaf == false)	{
		traverse(p->child_ptr[i]);
	}
	cout << endl;
}

void sort(int *p, int n) {
	int i, j, temp;
	for (i = 0; i < n; i++)	{
		for (j = i; j <= n; j++) {
			if (p[i] > p[j]) {
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
}

int split_child(Node *x, int i) {
	int j, mid;
	Node *np1, *np3, *y;
	np3 = new Node();
	np3->leaf = true;
	if (i == -1) {
		mid = x->data[2];
		x->data[2] = 0;
		x->n--;
		np1 = new Node();
		np1->leaf = false;
		x->leaf = true;
		for (j = 3; j < 5; j++)	{
			np3->data[j - 3] = x->data[j];
			np3->child_ptr[j - 3] = x->child_ptr[j];
			np3->n++;
			x->data[j] = 0;
			x->n--;
		}
		for (j = 0; j < 6; j++)	{
			x->child_ptr[j] = NULL;
		}
		np1->data[0] = mid;
		np1->child_ptr[np1->n] = x;
		np1->child_ptr[np1->n + 1] = np3;
		np1->n++;
		root = np1;
	}
	else {
		y = x->child_ptr[i];
		mid = y->data[2];
		y->data[2] = 0;
		y->n--;
		for (j = 3; j < 5; j++) {
			np3->data[j - 3] = y->data[j];
			np3->n++;
			y->data[j] = 0;
			y->n--;
		}
		x->child_ptr[i + 1] = y;
		x->child_ptr[i + 1] = np3;
	}
	return mid;
}

void insert(int a) {
	int i, temp;
	x = root;
	if (x == NULL) {
		root = new Node();
		x = root;
	}
	else {
		if (x->leaf == true && x->n == 5) {
			temp = split_child(x, -1);
			x = root;
			for (i = 0; i < (x->n); i++) {
				if ((a >= x->data[i]) && (a < x->data[i + 1])) {
					i++;
					break;
				}
				else if (a < x->data[0]) {
					break;
				}
				else {
					continue;
				}
			}
			x = x->child_ptr[i];
		}
		else {
			while (x->leaf == false){
				for (i = 0; i < (x->n); i++){
					if ((a >= x->data[i]) && (a < x->data[i + 1])){
						i++;
						break;
					}
					else if (a < x->data[0]){
						break;
					}
					else{
						continue;
					}
				}
				if ((x->child_ptr[i])->n == 5) {
					temp = split_child(x, i);
					x->data[x->n] = temp;
					x->n++;
					continue;
				}
				else{
					x = x->child_ptr[i];
				}
			}
		}
	}
	x->data[x->n] = a;
	sort(x->data, x->n);
	x->n++;
}
int main() {
	int i, n, t;
	cout << "enter the no of elements to be inserted\n";
	cin >> n;
	for (i = 0; i < n; ++i)	{
		cout << "enter the element\n";
		cin >> t;
		insert(t);
		cout << "current tree---\n";
		traverse(root);
		cout << "-------end-----\n";
	}

	cout << "traversal of constructed tree\n";
	traverse(root);
	getch();
}
