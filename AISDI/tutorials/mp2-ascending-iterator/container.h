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

#pragma once
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class OwnIter;

template <class T>
class OwnContainer: public vector<T>
{
public:
	typedef vector<T> Collection;
	explicit OwnContainer(int size = 0) : vector<T>(size) {};
	OwnContainer<T>(initializer_list<T> values) : vector<T>(values) {};

	OwnIter<T> getIterator() {
		return OwnIter<T>(this);
	}

	OwnIter<T> asc_begin() {
		vector<T>::iterator min_iter = begin();
		int min_index = 0, counter = min_index;
		for (vector<T>::iterator it = begin(); it != end(); ++it) {
			if (*it < *min_iter) {
				min_iter = it;
				min_index = counter;
			}
			++counter;
		}
		return OwnIter<T>(this, min_index);
	}

	OwnIter<T> asc_end() {
		return OwnIter<T>(this, size());
	}
};


template <class T>
class OwnIter
{
public:
	OwnIter<T>(const OwnContainer<T> *col, int index = 0) : owner(col), count(index) {}

	bool operator== (OwnIter<T> & otherIter) {
		return (count == otherIter.count && owner == otherIter.owner) ? true : false;
	}

	bool operator!= (OwnIter<T> & otherIter) {
		return !operator==(otherIter);
	}

	OwnIter<T> operator++ () {
		for (int i = count+1; i != (*owner).size(); ++i) {
			if ((*owner)[i] == (*owner)[count])
			{
				count = i;
				return OwnIter<T>((owner), i);
			}
		}
		bool found = false;
		int best = (*owner)[0];
		for (int i = 0; i != (*owner).size(); ++i) {
			if (((*owner)[count] < (*owner)[i]) && (!found || ((*owner)[i] < (*owner)[best]))) {
				best = i;
				found = true;
			}
		}
		if (found) {
			count = best;
			return OwnIter<T>((owner), best);
		}
		else {
			count = (*owner).size();
			return OwnIter<T>((owner), (*owner).size());
		}
	}

	T operator* () const {
		return (*owner)[count];
	}
private:
	const OwnContainer<T> *owner;
	int count;
};
