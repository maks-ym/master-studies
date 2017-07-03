/**
 * Copyright (C) 2017-01-02 Maks-ym (hereafter "Author")
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
 * merge sort implementation
 */

#include <iostream>
#include <algorithm>

template <typename T>
void merge_sort(T* arr, T* temp_arr, size_t size)
{
	if (size <= 1) {
		return;
	}

	//breaking the array into halfs to sort
	size_t size_l = size / 2;
	size_t size_r = size - size_l;

	merge_sort(arr, temp_arr, size_l);
	merge_sort(arr + size_l, temp_arr + size_l, size_r);

	//pointer for the left part
	T* ptr_l = arr;
	//middle element is end for left part and first for the right part
	T* const middle = arr + size_l;
	//pointer for the right part
	T* ptr_r = middle;
	T* const end = arr + size;
	//pointer for output (merged left and right parts)
	T* output_ptr = temp_arr;

	while (true) {

		*output_ptr++ = (*ptr_l <= *ptr_r) ? *ptr_l++ : *ptr_r++;

		if (ptr_l == middle) {
			std::copy(ptr_r, end, output_ptr);
			break;
		}
		if (ptr_r == end) {
			std::copy(ptr_l, middle, output_ptr);
			break;
		}
	}

	//copy the result to the main array
	std::copy(temp_arr, temp_arr + size, arr);
}

int main() {

	int numbers[] = { 236,7,4,5,654,2,67,3,8,6,7 };
	int n = sizeof(numbers) / sizeof(numbers[0]);
	int* numbers2 = new int[n];
	for (int i = 0; i < n; ++i) {
		numbers2[i] = numbers[i];
	}

	for (int i = 0; i < n; ++i) {
		std::cout << numbers[i] << " " << std::endl;
	}
	std::cout << std::endl;
	merge_sort(numbers, numbers2, n);
	n = sizeof(numbers) / sizeof(numbers[0]);
	for (int i = 0; i < n; ++i) {
		std::cout << numbers[i] << " " << std::endl;
	}
}
