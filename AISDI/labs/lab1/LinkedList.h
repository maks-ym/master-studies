#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi {

template <typename Type>
class LinkedList;

//template <typename Type>
//class LinkedList<Type>::ConstIterator;
//
//template <typename Type>
//class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator;

template<typename Type>
class ListNode
{
    ListNode( const Type & d = Type(),
              ListNode *p = nullptr, ListNode *n = nullptr)
              :data( d ), prev( p ), next( n ) {}

    Type data;
    ListNode *prev;
    ListNode *next;
    friend class LinkedList<Type>::const_iterator;
    friend class LinkedList<Type>::iterator;
    friend class LinkedList<Type>;
};

template <typename Type>
class LinkedList
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

  LinkedList(){
    init();
  }

  LinkedList(std::initializer_list<Type> l)
  {
    init();
    if(l.size() == 0)
        return;
    for (typename std::initializer_list<Type>::iterator it = l.begin(); it != l.end(); ++it)
        append(*it);
  }

  LinkedList(const LinkedList& other)
  {
    init();
    *this = other;
  }

  LinkedList(LinkedList&& other)
  {
    init();
    listSize = other.listSize;
    head = other.head;
    tail = other.tail;

    other.listSize = 0;
    other.head = nullptr;
    other.tail = nullptr;

  }

  ~LinkedList() {
    makeEmpty();
    delete head;
    delete tail;
  }

  LinkedList& operator=(const LinkedList& other) {
    if(this == &other) {
        return *this;
    }

    makeEmpty();
    const_iterator itr = other.begin();
    while (itr != other.end() ) {
        append( *itr++ );
    }
    return *this;
  }

  LinkedList& operator=(LinkedList&& other){
      if(this != &other){
        makeEmpty();
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
      }
      return *this;
  }

  bool isEmpty() const
  {
    return begin() == end();
  }

  size_type getSize() const {
    return listSize;
  }

  void append(const Type& item)
  {
//    insert( end(), item);
    tail->prev->next = new node(item, tail->prev, tail);
    tail->prev = tail->prev->next;
    ++listSize;
  }

  void prepend(const Type& item)
  {
    insert( begin(), item);
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {
//    if((insertPosition.head != NULL) &&

//       (insertPosition.current != NULL) &&
//       (insertPosition.current != head) &&
//       (insertPosition != end()) &&
//       (insertPosition.head != head))

        node *p = insertPosition.current;
        p->prev->next = new node(item, p->prev, p);
        p->prev = p->prev->next;
        ++listSize;
  }

  Type popFirst()
  {
    Type tmp = *begin();
    erase(begin());
    return tmp;
  }

  Type popLast()
  {
    Type tmp = *end();
    erase(end());
    return tmp;
  }

  void erase(const const_iterator& position)
  {
    if((position.head != NULL) &&
       (position.current != NULL) &&
       (position.current != head) &&
       (position != end()) &&
       (position.head != head))
       {
            node *p = position.current;
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            --listSize;
       }
  }

  void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
  {
    for(iterator itr = firstIncluded; itr != lastExcluded; )
        erase(itr);
  }

  iterator begin()
  {
    iterator itr( *this, head->next );
    return itr;
  }

  iterator end()
  {
    return iterator(*this, tail);
  }

  const_iterator cbegin() const
  {
    const_iterator itr( *this, head->next );
    return itr;
  }

  const_iterator cend() const
  {
    return const_iterator(*this, tail);
  }

  const_iterator begin() const
  {
    return cbegin();
  }

  const_iterator end() const
  {
    return cend();
  }

//  friend class ConstIterator<Type>;
//  friend class Iterator<Type>;

  private:
      typedef ListNode<Type> node;

      unsigned int listSize;
      node *head;
      node *tail;

      void init () {
        listSize = 0;
        head = new node;
        tail = new node;
        head->next = tail;
        tail->prev = head;
        head->prev = nullptr;
        tail->next = nullptr;
      };
      void makeEmpty() {
        while(!isEmpty()) {
            popFirst();
        }
      };
};

template <typename Type>
class LinkedList<Type>::ConstIterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename LinkedList::value_type;
  using difference_type = typename LinkedList::difference_type;
  using pointer = typename LinkedList::const_pointer;
  using reference = typename LinkedList::const_reference;

  explicit ConstIterator(const LinkedList<Type> & source = nullptr, node *p = nullptr)
        : head(source.head),tail(source.tail), current(p) {};

  reference operator*() const
  {
      if(current->next == nullptr)
        throw std::out_of_range("Out of range.");
    return retrieve();
  }

  ConstIterator& operator++()
  {
      if(current == tail)
        throw std::out_of_range("Out of range.");
    if(current->next != tail)
        current = current->next;
    return *this;
  }

  ConstIterator operator++(int)
  {
    LinkedList<Type>::ConstIterator old = *this;
    operator++();
    return old;
  }

  ConstIterator& operator--()
  {
    if( current->prev == head->prev )
        throw std::out_of_range("Out of range.");
    if(current->prev != head)
        current = current->prev;
    return *this;
  }

  ConstIterator operator--(int)
  {
    LinkedList<Type>::ConstIterator old = *this;
    operator--();
    return old;
  }

  ConstIterator operator+(difference_type d) const
  {
    const_iterator tmp = *this;
    for (unsigned int i = 0 ; i < d && tmp.current != tail; ++i)
        ++tmp;
    return tmp;
  }

  ConstIterator operator-(difference_type d) const
  {
    const_iterator tmp = *this;
    for (unsigned int i = 0 ; i < d && tmp.current != head; ++i)
        --tmp;
    return tmp;
  }

  bool operator==(const ConstIterator& other) const
  {
    return (current == other.current) &&
           (head == other.head) &&
           (tail == other.tail);
  }

  bool operator!=(const ConstIterator& other) const
  {
    return !( *this == other );
  }

protected:
    typedef ListNode<Type> node;
    node *head;
    node *tail;
    node *current;

    friend class LinkedList<Type>;

    Type & retrieve() const {
        return current->data;
    };


};

template <typename Type>
class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator
{
public:
  using pointer = typename LinkedList::pointer;
  using reference = typename LinkedList::reference;

  explicit Iterator(const LinkedList<Type> & source = nullptr, node *p = nullptr) : ConstIterator(source, p) {}

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
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};

}

#endif // AISDI_LINEAR_LINKEDLIST_H
