/**
 * Copyright (C) 2016-11-26 Maks-ym (hereafter "Author")
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
