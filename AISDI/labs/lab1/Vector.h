#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi
{

template <typename Type>
class Vector
{

public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using value_type = Type;
  using pointer = Type*;
  using reference = Type&;
  using const_pointer = const Type*;
  using const_reference = const Type&;

  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  Vector(int initSize = 0): vecSize(initSize), vecCapacity(initSize) {
    objects = new Type[vecCapacity + 1];
  }

  Vector(std::initializer_list<Type> l) {
    vecSize = 0;
    vecCapacity = l.size();
    objects = new Type[l.size() + 1];
      for (typename std::initializer_list<Type>::iterator it = l.begin(); it != l.end(); ++it)
        append(*it);
  }

  Vector(const Vector& other) {
    vecSize = 0;
    vecCapacity = other.getSize();
    objects = new Type[vecCapacity+1];
    for(iterator it = other.begin(); it != other.end(); ++it) {
        append(*it);
    }
  }

  Vector(Vector&& other) {
    vecSize = other.vecSize;
    vecCapacity = other.vecCapacity;
    objects = new Type[vecCapacity];
    for(unsigned int i = 0; i < other.vecSize; ++i)
        objects[i] = other.objects[i];
    other.vecSize = 0;
    other.vecCapacity = 0;
  }

  ~Vector(){
    delete [] objects;
  }

  Vector& operator=(const Vector& other)
  {
    vecSize = other.vecSize;
    vecCapacity = other.vecCapacity;
    for(unsigned int i = 0; i < vecSize; ++i) {
        objects[i] = other.objects[i];
    }
    return *this;
  }

  Vector& operator=(Vector&& other)
  {
    vecSize = other.vecSize;
    vecCapacity = other.vecCapacity;
    for(unsigned int i = 0; i < vecSize; ++i) {
        objects[i] = other.objects[i];
    }
    other.vecSize = 0;
    other.vecCapacity = 0;
    return *this;
  }

  Type & operator [] (int index) {
    return objects[index];
  }

  const Type & operator [] (int index) const {
    return objects[index];
  }

  bool isEmpty() const
  {
    return !(bool)vecSize;
  }

  size_type getSize() const
  {
    return vecSize;
  }

  size_type getCapacity() const {
    return vecCapacity;
  }

  void append(const Type& item)
  {
      if( vecSize == vecCapacity) {
        reserve(2 * vecCapacity + 1);
      }
    objects[vecSize++] = item;
  }

  void prepend(const Type& item)
  {
      if( vecSize == vecCapacity) {
        reserve(2 * vecCapacity + 1);
      }
    for(int i = vecSize; i > 0 ; --i) {
        objects[i] = objects[i-1];
    }
    objects[0] = item;
    vecSize++;
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {
      if( vecSize == vecCapacity) {
        reserve(2 * vecCapacity + 1);
      }
    if(insertPosition == end())
        append(item);
    else {
    iterator it = (end()-1);
    append(*it);
    for(; it != insertPosition; --it) {
        *it = *(it-1);
    }
    *it = item;
    }
  }

  void reserve(unsigned int newCapacity) {
    Type * oldObjects = objects;
    int numToCopy = newCapacity < vecSize ?
                    newCapacity : vecSize;
    objects = new Type[ newCapacity ];
    for (int i = 0 ; i < numToCopy; ++i) {
        objects[i] = oldObjects[i];
    }
    vecSize = numToCopy;
    vecCapacity = newCapacity;

    delete [] oldObjects;
  }

  Type popFirst()
  {
    if(vecSize == 0)
        throw std::logic_error("Logic error: can't pop from the empty vector");
    Type tmp = objects[0];
    for(unsigned int i = 0; i < vecSize; ++i) {
        objects[i] = objects[i+1];
    }
    --vecSize;
    return tmp;
  }

  Type popLast()
  {
    if(vecSize == 0)
        throw std::logic_error("Logic error: can't pop from the empty vector");
    Type tmp = objects[vecSize-1];
    --vecSize;
    return tmp;
  }

  void erase(const const_iterator& position) {
    if(position == end())
        throw std::out_of_range("Error: Can't erase. Out of range");
    for(iterator it = position+1; it != end(); ++it) {
        *(it-1) = *it;
    }
    vecSize -= 1;
  }

  void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded) {
    if(firstIncluded == end())
        throw std::out_of_range("Error: Can't erase. Out of range");
    if(firstIncluded == lastExcluded)
        return;
    difference_type iter_diff = 0;
    for(iterator it = firstIncluded; it != lastExcluded; ++it){
        ++iter_diff;
    }
    for(iterator it = firstIncluded; (it + iter_diff) != end(); ++it) {
        *it = *(it + iter_diff);
    }
    vecSize -= (unsigned)iter_diff;
  }

  iterator begin() {
    return const_iterator(*this, 0);
  }

  iterator end() {
    return const_iterator( *this, (int)vecSize);
  }

  const_iterator cbegin() const {
    return const_iterator( *this, 0);
  }

  const_iterator cend() const {
    return const_iterator( *this, (int)vecSize);
  }

  const_iterator begin() const {
    return cbegin();
  }

  const_iterator end() const {
    return cend();
  }

private:
    size_type vecSize;
    size_type vecCapacity;
    Type* objects;
};

template <typename Type>
class Vector<Type>::ConstIterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename Vector::value_type;
  using difference_type = typename Vector::difference_type;
  using pointer = typename Vector::const_pointer;
  using reference = typename Vector::const_reference;

  ConstIterator(): owner(nullptr), curIndex(0) {};

  ConstIterator(const Vector<Type> &v, int index = 0) {
    owner = &v;
    curIndex = index;
  }

  reference operator*() const
  {
    if(curIndex == (*owner).vecSize)
        throw std::out_of_range("Error! Out of range.");
    return (*owner)[curIndex];
  }

  ConstIterator& operator++()
  {
    if(curIndex+1 > (*owner).vecSize)
        throw std::out_of_range("Error. Iterator is going to be out of range");
    ++curIndex;
    *this = ConstIterator(*owner, curIndex);
    return (ConstIterator&)*this;
  }

  ConstIterator operator++(int)
  {
    if(curIndex+1 > (*owner).getSize())
        throw std::out_of_range("Error. Iterator is going to be out of range");
    int tmpIndex = curIndex;
    ++curIndex;
    return ConstIterator(*owner, tmpIndex);
  }

  ConstIterator& operator--()
  {
    if((int)curIndex-1 < 0)
        throw std::out_of_range("Error. Iterator is going to be out of range");
    --curIndex;
    *this = ConstIterator(*owner, curIndex);
    return (ConstIterator&)*this;
  }

  ConstIterator operator--(int)
  {
    if((int)curIndex-1 < 0)
        throw std::out_of_range("Error. Iterator is going to be out of range");
    int tmpIndex = curIndex;
    --curIndex;
    ConstIterator retVal = ConstIterator(*owner, tmpIndex);
    return retVal;
  }

  ConstIterator operator+(difference_type d) const
  {
    const_iterator tmp = *this;
    for(int i = 0; i < d && tmp != (*owner).end(); ++i) {
		 ++tmp;
    }
    return tmp;
  }

  ConstIterator operator-(difference_type d) const
  {
    const_iterator tmp = *this;
    for(int i = 0; i < d && tmp != (*owner).begin(); ++i) {
		 --tmp;
    }
    return tmp;
  }

  bool operator==(const ConstIterator& other) const
  {
    return (*this).curIndex == other.curIndex ? true : false;
  }

  bool operator!=(const ConstIterator& other) const
  {
    return !operator==(other);
  }

  private:
      const Vector<Type> *owner;
      unsigned mutable curIndex;
};

template <typename Type>
class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
{
public:
  using pointer = typename Vector::pointer;
  using reference = typename Vector::reference;

  explicit Iterator()
  {}

  Iterator(const ConstIterator& other)
    : ConstIterator(other)
  {}

  Iterator& operator++()
  {
    ConstIterator::operator++();
    return *this;
  }

  Iterator operator++(int)
  {
    auto result = *this;
    ConstIterator::operator++();
    return result;
  }

  Iterator& operator--()
  {
    ConstIterator::operator--();
    return *this;
  }

  Iterator operator--(int)
  {
    auto result = *this;
    ConstIterator::operator--();
    return result;
  }

  Iterator operator+(difference_type d) const
  {
    return ConstIterator::operator+(d);
  }

  Iterator operator-(difference_type d) const
  {
    return ConstIterator::operator-(d);
  }

  reference operator*() const
  {
    return const_cast<reference>(ConstIterator::operator*());
  }
};
}

#endif // AISDI_LINEAR_VECTOR_H
