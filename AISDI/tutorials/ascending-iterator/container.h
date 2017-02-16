/*---------------------------------------------
Author: Maksym Bakhmut
---------------------------------------------*/
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
