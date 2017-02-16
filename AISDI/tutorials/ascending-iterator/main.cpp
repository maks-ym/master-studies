/*---------------------------------------------
Author: Maksym Bakhmut
---------------------------------------------*/

#include <iostream>
#include <vector>
#include <stdio.h>
#include "container.h"

using namespace std;

int main() {
	/* Two variants of adding elements are possible */

	OwnContainer<int> arr({2,3,6,1,6,7,5,34,4,45,1245,4,2,323,65,76,90});

	for (OwnIter<int> it = arr.asc_begin(); it != arr.asc_end(); ++it) {
		std::cout << (*it) << std::endl;
	}


	OwnContainer<char> char_arr;
	char_arr.push_back('a');
	char_arr.push_back('f');
	char_arr.push_back('g');
	char_arr.push_back('e');
	char_arr.push_back('g');
	char_arr.push_back('l');
	char_arr.push_back('k');
	char_arr.push_back('n');
	char_arr.push_back(';');

	for (OwnIter<char> it = char_arr.asc_begin(); it != char_arr.asc_end(); ++it) {
		std::cout << (*it) << std::endl;
	}

	system("pause");
	return 0;
}
