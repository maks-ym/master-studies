#ifndef AISDI_MAPS_HASHMAP_H
#define AISDI_MAPS_HASHMAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <cstring>
#include <string>
#include <iostream>

namespace aisdi
{

template <typename KeyType, typename ValueType>
class HashMap
{
public:
  using key_type = KeyType;
  using mapped_type = ValueType;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  HashMap() :  hash_t{0}, size(0) {
//    memset(hash_t, 0, table_size * sizeof(Node *));
  }

  HashMap(std::initializer_list<value_type> list)
  {
    typename std::initializer_list<value_type>::iterator iter = list.begin();
    for(; iter != list.end(); ++iter) {
        operator[]((*iter).first) = (*iter).second;
    }
  }

  HashMap(const HashMap& other)
  {
    if(other == *this ) {
        return;
    }
    size = 0;
    if(other.size == 0 ) {
        return;
    }
    const_iterator iter = other.begin();
    for(iter = other.begin(); iter != end(); ++iter) {
        operator[]((*iter).first) = (*iter).second;
    }
  }

  HashMap(HashMap&& other)
  {
    std::memcpy(hash_t,       other.hash_t, table_size * sizeof(Node *));
    std::memset(other.hash_t, 0,            table_size * sizeof(Node *));

    size = other.size;
    other.size = 0;
  }

//    ~HashMap() {
//        clear();
//        std::memset(hash_t, 0,            table_size * sizeof(Node *));
//    }

  HashMap& operator=(const HashMap& other)
  {
    if(  other != *this ) {
    std::cout << "operator =" << std::endl;
        clear();
    std::cout << "clear() done" << std::endl;
        for(const_iterator iter = other.begin(); iter != other.end(); ++iter) {

            operator[]((*iter).first) = (*iter).second;
        }
    std::cout << "loop done" << std::endl;
        size = other.size;
    }
    return *this;
  }

  HashMap& operator=(HashMap&& other)
  {
    if( other != *this ) {
        clear();
        hash_t = other.hash_t;
//        std::memcpy(hash_t,       other.hash_t, table_size * sizeof(Node *));
//        std::memset(other.hash_t, 0,            table_size * sizeof(Node *));
        size = other.size;
        other.size = 0;
    }
    return this;
  }

  bool isEmpty() const
  {
    return size == 0;
  }

  mapped_type& operator[](const key_type& key)
  {
    iterator iter = find(key);
    if( iter != end() ) {
        return (*iter).second;
    }
    else {
        return insert(key);
    }
  }

  const mapped_type& valueOf(const key_type& key) const
  {
    const_iterator iter = find(key);
    if( iter != end() ) {
        return (*iter).second;
    }
    else {
        throw std::out_of_range("Easy! There is no such element.");
    }
  }

  mapped_type& valueOf(const key_type& key)
  {
    iterator iter = find(key);
    if( iter != end() ) {
        return (*iter).second;
    }
    else {
        throw std::out_of_range("Easy! There is no such element.");
    }
  }

  const_iterator find(const key_type& key) const
  {
//    std::cout << "\n find const -- begin \n" << std::endl;
    size_type hash_i = hash_function( key );
    Node * found_node = hash_t[hash_i];
    while( found_node != nullptr && found_node->data.first != key ) {
        found_node = found_node->next;
    }
    return const_iterator( *this, found_node );
  }

  iterator find(const key_type& key)
  {
    size_type hash_i = hash_function( key );
//    std::cout << "\n find  -- begin \n" << std::endl;
    Node * found_node = hash_t[hash_i];
//    std::cout << "\n found_node created \n" << std::endl;
//    std::cout << "\n while loop next \n" << std::endl;

    while( found_node != nullptr && found_node->data.first != key  ) {
//    std::cout << "iteration begin \n" << std::endl;
        found_node = found_node->next;
//    std::cout << "iteration end \n" << std::endl;
    }
    return iterator( *this, found_node );
  }

  void remove(const key_type& key)
  {
    iterator to_delete = find( key );
    if( to_delete != end() ) {
        remove( to_delete );
    }
    else {
        throw std::out_of_range("Huh.. You're going to delete a non-existent element. Is it possible at all?");
    }
  }

  void remove(const const_iterator& it)
  {
    if( it == end() ) {
        throw std::out_of_range("Huh.. You're going to delete a non-existent element. Is it possible at all?");
    }
    size_type hash_i = hash_function( (*it).first );
    if( it.current->prev ) {
        it.current->prev->next = it.current->next;
    }
    else {
        hash_t[hash_i] = it.current->next;
    }
    if( it.current->next ) {
        it.current->next->prev = it.current->prev;
    }
    --size;
    delete it.current;
  }

  size_type getSize() const
  {
    return size;
  }

  bool operator==(const HashMap& other) const
  {
    iterator it_1 = begin(), it_2 = other.begin();
    while( it_1 != end() && it_2 != other.end() ) {
//        if( (it_1->first != it_2->first) || (it_1->second != it_2->second) ) {
        if( *it_1 != *it_2  ) {
            return false;
        }
        ++it_1; ++it_2;
    }
    if(it_1 == end() && it_2 == other.end()) {
        return true;
    }
    return false;
  }

  bool operator!=(const HashMap& other) const
  {
    return !(*this == other);
  }

  iterator begin()
  {
    size_type hash_i = 0;
    while( hash_t[hash_i] == nullptr && hash_i < table_size - 1 ) {
        ++hash_i;
    }
//    std::cout << hash_i << " " << (hash_t[hash_i] == nullptr) << std::endl;
    return iterator( *this, hash_t[hash_i] );
  }

  iterator end()
  {
    return iterator( *this, nullptr );
  }

  const_iterator cbegin() const
  {
    size_type hash_i = 0;
    while( hash_t[hash_i] == nullptr && hash_i < table_size ) {
        ++hash_i;
    }
    return iterator( *this, hash_t[hash_i] );
  }

  const_iterator cend() const
  {
    return const_iterator( *this, nullptr );
  }

  const_iterator begin() const
  {
    return cbegin();
  }

  const_iterator end() const
  {
    return cend();
  }

private:
    struct Node {
        value_type data;
        Node* prev;
        Node* next;

        Node(value_type d, Node* p = nullptr, Node* n = nullptr) : data(d), prev(p), next(n) {}
    };

    static const size_type table_size = 32719;
    Node* hash_t[table_size];
    size_type size;

    inline size_type hash_function(const key_type& m) const {
        //Jenkins hash function
        std::string str = std::to_string(m);
        size_type len = str.length();
        uint32_t hash, i;
        for(hash = i = 0; i < len; ++i)
        {
            hash += str[i];
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }

        hash += (hash << 3);
        hash ^= (hash << 11);
        hash += (hash << 15);
//        return hash & ((1 << 14) - 1);
        hash %= table_size-1;
//        hash;
//        std::cout << hash << std::endl;
        return hash;
    };

    mapped_type& insert( const key_type& key ) {
        return insert( (value_type)std::make_pair(key, mapped_type()) );
    }
    mapped_type& insert( value_type new_pair ) {
//    std::cout << "\n insert func \n" << std::endl;
        size_type hash_i = hash_function(new_pair.first);

//    std::cout << "\n hash  \n" << hash_i << std::endl;

		Node * next_node = hash_t[hash_i];

		Node * new_node = new Node( new_pair, nullptr, next_node);
		if(next_node != nullptr)
		   next_node->prev = new_node;
		hash_t[hash_i] = new_node;

        ++size;
//    std::cout << "\n after insert \n" << std::endl;
		return (*new_node).data.second;
    }

    void clear() {
//        for( iterator iter = begin(); iter != end(); ++iter ) {
//            remove(iter);
//        }
//    std::cout << "we are in clear" << std::endl;
        for(size_type hash_i = 0; hash_i < table_size; ++hash_i) {
//    std::cout << "loop iteration" << std::endl;
            if(hash_t[hash_i] == nullptr) {
//    std::cout << "nullptr - go further" << std::endl;
                continue;
            }
            else {
//    std::cout << "NOT a nullptr - going to delete a list at hash_i" << std::endl;
                while(hash_t[hash_i]->next != nullptr) {
//    std::cout << "NOT a nullptr - there is next element at hash_i- going to delete a next element hash_i" << std::endl;
                    Node * tmp = hash_t[hash_i];
                    hash_t[hash_i] = hash_t[hash_i]->next;
                    hash_t[hash_i]->prev = nullptr;
                    delete tmp;
                    size--;
                }
//                delete hash_t[hash_i];
                size--;
//    std::cout << "NOT a nullptr - going to delete a last element hash_i" << std::endl;
//    std::cout << table_size << " = - = table size" << std::endl;
//    std::cout << size << " = - = current size" << std::endl;
//    std::cout << hash_i << std::endl;
//                    delete hash_t[hash_i];
            }
        }
        size = 0;
    }
};

template <typename KeyType, typename ValueType>
class HashMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename HashMap::const_reference;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename HashMap::value_type;
  using pointer = const typename HashMap::value_type*;

//  explicit ConstIterator() : owner(nullptr), current(nullptr) {}

  explicit ConstIterator( const HashMap& o, Node* n = nullptr)
  : owner( &o ), current( n ) {}

  ConstIterator(const ConstIterator& other)
  {
    owner = other.owner;
    current = other.current;
  }

  ConstIterator& operator++()
  {
    if( current == nullptr ) {
        throw std::out_of_range("Oops! You're gonna fall out into outer space... Can't increase.");
    }
    if( current->next ) {
        current = current->next;
        return *this;
    }
    size_type hash_i = (*owner).hash_function( current->data.first );
    ++hash_i;
    while( (*owner).hash_t[hash_i] == nullptr && (hash_i + 1) < (*owner).table_size ) {
        ++hash_i;
    }
    current = (*owner).hash_t[hash_i];
    return *this;
  }

  ConstIterator operator++(int)
  {
    Node* tmp = current;
    operator++();
    return ConstIterator( *owner, tmp );
  }

  ConstIterator& operator--()
  {
//    std::cout << "\n operator -- \n" << std::endl;
//    std::cout << "\n check end\n" << std::endl;
    if( current == nullptr ) {
        size_type hash_i = (*owner).table_size - 1;
//        std::cout << (bool)((*owner).hash_t[hash_i] == nullptr) << std::endl;  //
        while( (*owner).hash_t[hash_i] == nullptr && 0 < (hash_i - 1) ) {
//    std::cout << "\n  iteration \n" << std::endl;
            --hash_i;
        }
        if( (*owner).hash_t[hash_i] == nullptr ) {
            throw std::out_of_range("Oops! You're gonna fall out into outer space... Can't decrease.");
        }
//        std::cout << "\n hash found search for last element \n" << std::endl;
//        std::cout << hash_i<< std::endl;
        current = (*owner).hash_t[hash_i];
        while( current->next != nullptr ) {
            current = current->next;
        }
        return *this;
    }
//    else if( (*owner).hash_function( current->data.first ) == 0 && current->prev == nullptr ) {
    else if( *this == (*owner).begin() ) {
//    std::cout << "\n check begin\n" << std::endl;
        throw std::out_of_range("Oops! You're gonna fall out into outer space... Can't decrease.");
    }
//    std::cout << "\n check previous \n" << std::endl;
    if( current->prev ) {
        current = current->prev;
        return *this;
    }
//    std::cout << "\n  search in hash table \n" << std::endl;
    size_type hash_i = (*owner).hash_function( current->data.first );
    --hash_i;
    while( (*owner).hash_t[hash_i] == nullptr && 0 < (hash_i - 1) ) {
        --hash_i;
    }
    current = (*owner).hash_t[hash_i];
//  std::cout << "\n hash found search for last element \n" << std::endl;
    while( current->next ) {
        current = current->next;
    }
//  std::cout << "\n return \n" << std::endl;
    return *this;
  }

  ConstIterator operator--(int)
  {
    Node* tmp = current;
    operator--();
    return ConstIterator( *owner, tmp );
  }

  reference operator*() const
  {
    if ( current == nullptr ) {
        throw std::out_of_range("Professional Out-of-range-when-dereferencing-end() is here!");
    }
    return current->data;
  }

  pointer operator->() const
  {
    return &this->operator*();
  }

  bool operator==(const ConstIterator& other) const
  {
    return ((owner == other.owner) && (current == other.current));
  }

  bool operator!=(const ConstIterator& other) const
  {
    return !(*this == other);
  }

private:
    const HashMap<KeyType, ValueType>* owner;
    Node* current;

    friend class HashMap<KeyType, ValueType>;
};

template <typename KeyType, typename ValueType>
class HashMap<KeyType, ValueType>::Iterator : public HashMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename HashMap::reference;
  using pointer = typename HashMap::value_type*;

  explicit Iterator() {}

  Iterator( const HashMap& o, Node* n ) : ConstIterator( o, n ) {}

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

  pointer operator->() const
  {
    return &this->operator*();
  }

  reference operator*() const
  {
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};

}

#endif /* AISDI_MAPS_HASHMAP_H */
