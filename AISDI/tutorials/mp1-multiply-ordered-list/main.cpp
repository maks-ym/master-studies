/**
 * Copyright (C) 2016-10-26 Maks-ym (hereafter "Author")
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

#include <iostream>
#include <typeinfo>

using namespace std;

class List {
    struct Node {
        int number;
        char letter;
        Node* nextNumber;
        Node* nextLetter;
        Node(int& numValue, char& charValue):number(numValue), letter(charValue), nextNumber(), nextLetter() {};
    };
    Node* headNumber;
    Node* headLetter;

public:
    List();
    ~List();
    void addItem(int, char);
    void showListByNumbers();
    void showListByLetters();
    bool isEmpty();
    Node* findPrevNumber(int);
    Node* findPrevLetter(char);
};

List::List() {
    headNumber = 0;
    headLetter = 0;
    cout << "List created" << endl;
}

List::~List() {
    if(isEmpty()) return;
    Node *tmp = headNumber->nextNumber;
    while(!tmp == 0)     {
         delete headNumber;
         headNumber = tmp;
         tmp = tmp->nextNumber;
    }
    delete headNumber;
    headNumber = tmp;
    cout << "List deleted." << endl;
}

void List::addItem(int userNumber, char userLetter) {
    Node* item = new Node(userNumber, userLetter);
    if(isEmpty())     {
        item->nextNumber = NULL;
        item->nextLetter = NULL;
        headNumber = item;
        headLetter = item;
    }
    else {
        if(userNumber < headNumber->number) {
            item->nextNumber = headNumber;
            headNumber = item;
        }
        else {
            Node* prevNum = findPrevNumber(userNumber);
            item->nextNumber = prevNum->nextNumber;
            prevNum->nextNumber = item;
        }
        if(userLetter < headLetter->letter) {
            item->nextLetter = headLetter;
            headLetter = item;
        }
        else {
            Node* prevLetter = findPrevLetter(userLetter);
            item->nextLetter = prevLetter->nextLetter;
            prevLetter->nextLetter = item;
        }
    }
}

List::Node* List::findPrevNumber(int key) {
    Node* current = headNumber;
    if(key < current->number) return headNumber;
    while(!(current->nextNumber == 0)) {
        if((current->number <= key && current->nextNumber->number > key) || current->nextNumber == 0){
            break;
        }
        current = current->nextNumber;
    }
    return current;
}

List::Node* List::findPrevLetter(char key) {
    Node* current = headLetter;
    if(key < current->letter) return headLetter;
    while(!(current->nextLetter == 0))     {
        if((current->letter <= key && current->nextLetter->letter > key) || current->nextLetter == 0) break;
        current = current->nextLetter;
    }
    return current;
}

bool List::isEmpty() {
    return (headNumber == 0 && headLetter == 0);
}

void List::showListByNumbers() {
    if (isEmpty())     {
        cout << "List is empty!" << endl;
    }
    else     {
        cout << "[num, let]\taddress \tnext number\tnext letter"<< endl;
        cout << "-----------------------------------------------------------"<< endl;
        for(Node *tmp = headNumber; tmp != 0; tmp = tmp->nextNumber) {
            cout << "[" << tmp->number << "\t"<< tmp->letter << "]\t" << tmp << "\t" << tmp->nextNumber << "\t" << tmp->nextLetter <<  endl;
        }
        cout << "==========================================================="<< endl;
    }
}

void List::showListByLetters() {
    if (isEmpty()) {
        cout << "List is empty!" << endl;
    }
    else {
        cout << "[let, num];\taddress \tnext letter\tnext number"<< endl;
        cout << "-----------------------------------------------------------"<< endl;
        for(Node *tmp = headLetter; tmp != 0; tmp = tmp->nextLetter) {
            cout << "[" << tmp->letter << "\t"<< tmp->number << "]\t" << tmp << "\t" << tmp->nextLetter << "\t" << tmp->nextNumber << endl;
        }
        cout << "==========================================================="<< endl;
    }
}

int main() {
    List* my_list = new List;
    my_list->addItem(5, 'a');
    my_list->addItem(3, 'b');
    my_list->addItem(31, 'r');
    my_list->addItem(1, 'w');
    my_list->addItem(453, 'G');
    my_list->addItem(95, 'A');
    my_list->addItem(-51, 'z');

    my_list->showListByNumbers();
    my_list->showListByLetters();

    delete my_list;

    return 0;
}
