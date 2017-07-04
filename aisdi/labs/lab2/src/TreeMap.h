#ifndef AISDI_MAPS_TREEMAP_H
#define AISDI_MAPS_TREEMAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace aisdi
{

template <typename KeyType, typename ValueType>
class TreeMap
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

  struct Node {
    value_type node_data;
    Node * left;
    Node * right;
    Node * parent;

    Node(key_type key, mapped_type value, Node* p = nullptr) : node_data( std::make_pair(key, value) ), left( nullptr ), right( nullptr ), parent( p ) {};

  };

  TreeMap() : root(nullptr), tree_size(0) {}

  TreeMap(std::initializer_list<value_type> list) {
    root = nullptr;
    tree_size = 0;
    for( typename std::initializer_list<value_type>::iterator iter = list.begin(); iter != list.end(); ++iter) {
        operator[]((*iter).first) = (*iter).second;
    }
  }

  TreeMap(const TreeMap& other)
  {
    root = nullptr;
    tree_size = 0;
    for(const_iterator iter = other.begin(); iter != other.end(); ++iter) {
        operator[](iter->first) = iter->second;             // the same to initilizer list
    }
  }

  TreeMap(TreeMap&& other)
  {
    root = other.root;
    tree_size = other.tree_size;
    other.root = nullptr;
    other.tree_size = 0;
  }

  TreeMap& operator=(const TreeMap& other)
  {
    if(other == *this) {
        return *this;
    }
    clear(root);
//    if(other.root == nullptr) {
//        root = nullptr;
//        tree_size = 0;
//    }
    for(const_iterator iter = other.begin(); iter != other.end(); ++iter) {
        operator[](iter->first) = iter->second;             // the same to initilizer list
    }
    return *this;
  }

  TreeMap& operator=(TreeMap&& other)
  {
    if(other == *this) {
        return *this;
    }
    clear(root);
    root = other.root;
    tree_size = other.tree_size;
    other.root = nullptr;
    other.tree_size = 0;
    return *this;
  }

  bool isEmpty() const
  {
    return !tree_size;
  }

  mapped_type& operator[](const key_type& key)
  {
    return insert(key);
  }

  const mapped_type& valueOf(const key_type& key) const
  {
    const_iterator returnIter = find(key);
    if(returnIter != end()) {
    return returnIter->second;
    }
        throw std::out_of_range("There is no element with such key.");
  }

  mapped_type& valueOf(const key_type& key)
  {
    iterator returnIter = find(key);
    if(returnIter != end()) {
        return returnIter->second;
    }
        throw std::out_of_range("There is no element with such key.");
  }

  const_iterator find(const key_type& key) const
  {
    Node* current = root;
    while( current != nullptr ) {
        if(key < current->node_data.first && current->left) {
                current = current->left;
        }
        else if( current->node_data.first < key && current->right ) {
                current = current->right;
        }
        else if ( key == current->node_data.first ){
            return iterator(*this, current);
        }
        else {
            break;
        }
    }
    return end();
  }

  iterator find(const key_type& key)
  {
    Node* current = root;
    while( current != nullptr ) {
        if(key < current->node_data.first && current->left) {
                current = current->left;
        }
        else if( current->node_data.first < key && current->right ) {
                current = current->right;
        }
        else if ( key == current->node_data.first ){
            return iterator(*this, current);
        }
        else {
            break;
        }
    }
    return end();
  }

  void remove(const key_type& key)
  {
    remove(find(key));
  }

  void remove(const const_iterator& iter)
  {
    if(iter == end() ) {
        throw std::out_of_range("Error! Out of range.");
    }
//    iterator iter = iterator(it);
    if( iter.current->left && iter.current->right ) {
        iterator candidate = iter; ++candidate;
        iterator tmp = iter;
        iter.current->parent = candidate.current->parent;
        iter.current->left = candidate.current->left;
        iter.current->right= candidate.current->right;
        candidate.current->parent = tmp.current->parent;
        candidate.current->left = tmp.current->left;
        candidate.current->right= tmp.current->right;
        remove(iter);
        return;
    }
//    else if( !iter.current->left && !iter.current->right ) {
//        if ( iter.current->parent == nullptr) {
//            root == nullptr;
//        }
//        else if ( iter.current == iter.current->parent->left ) {
//            iter.current->parent->left == nullptr;
//        }
//        else {
//            iter.current->parent->right == nullptr;
//        }
//        delete iter.current;
//    }
    else {
        Node* child = (iter.current->left) ? iter.current->left
                    : (iter.current->right) ? iter.current->right
                    : nullptr;
        if ( iter.current->parent == nullptr) {
            root = child;
        }
        else if ( iter.current == iter.current->parent->left ) {
            iter.current->parent->left = child;
        }
        else {
            iter.current->parent->right = child;
        }
        delete iter.current;
    }
    --tree_size;
  }

  size_type getSize() const
  {
    return tree_size;
  }

  bool operator==(const TreeMap& other) const
  {
    if( tree_size != other.tree_size ) {
        return false;
    }
    for( iterator itr1 = begin(), itr2 = other.begin(); itr1 != end(); ++itr1, ++itr2 ) {
        if((*itr1).first != (*itr2).first || (*itr1).second != (*itr2).second ) {
            return false;
        }
    }
    return true;
  }

  bool operator!=(const TreeMap& other) const
  {
    return !(*this == other);
  }

  iterator begin()
  {
    return findMin(root);
  }

  iterator end()
  {
    return iterator(*this, nullptr);
  }

  const_iterator cbegin() const
  {
    return findMin(root);
  }

  const_iterator cend() const
  {
    return const_iterator(*this, nullptr);
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
    Node* root;
    size_type tree_size;

    void clear( Node* current ) {
        if(current == nullptr) {
            tree_size = 0;
            return;
        }
        if(current->left) {
            clear(current->left);
        }
        if (current->right) {
            clear(current->right);
        }
        delete current;
        --tree_size;
    }

    mapped_type& insert(key_type key) {
        Node* current = root;
        if(current == nullptr) {
            root = new Node(key, mapped_type(), current);
            current = root;
            ++tree_size;
            return (mapped_type&)current->node_data.second;
        }
        while(true) {
            if(key < current->node_data.first) {
                if (current->left) {
                    current = current->left;
                }
                else {
                    current->left = new Node(key, mapped_type(), current);
                    ++tree_size;
                    return (mapped_type&)current->left->node_data.second;
                }
            }
            else if ( current->node_data.first < key ) {
                if( current->right ) {
                    current = current->right;
                }
                else {
                    current->right = new Node(key, mapped_type(), current);
                    ++tree_size;
                    return (mapped_type&)current->right->node_data.second;
                }
            }
            else {
                return (mapped_type&)current->node_data.second;
            }
        }
    }

    const_iterator findMin( Node* n ) const {
        if( n == nullptr ) {
            return end();
        }
        while(n->left) {
            n = n->left;
        }
        return const_iterator(*this, n);
    }

    iterator findMin( Node* n ) {
        if( n == nullptr ) {
            return end();
        }
        while(n->left) {
            n = n->left;
        }
        return iterator(*this, n);
    }

    const_iterator findMax( Node* n ) const {
        if( n == nullptr ) {
            return end();
        }
        auto itr = const_iterator(*this, n);
        while(itr.current->right) {
            ++itr;
        }
        return itr;
    }

    iterator findMax( Node* n ) {
        if( n == nullptr ) {
            return end();
        }
        auto itr = iterator(const_iterator(*this, n));
        while(itr->right) {
            ++itr;
        }
        return itr;
    }
};


template <typename KeyType, typename ValueType>
class TreeMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename TreeMap::const_reference;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename TreeMap::value_type;
  using pointer = const typename TreeMap::value_type*;

  explicit ConstIterator( const TreeMap & source, Node *p = nullptr )
        : owner(&source), current(p) {};

  ConstIterator(const ConstIterator& other)
  {
    owner = other.owner;
    current = other.current;
  }

  ConstIterator& operator++()
  {
    if( !current ) {
        throw std::out_of_range("Error! You're gonna to leave to outer space! (Can't increase)");
    }
    if( current->right ) {
        current = current->right;
        while(current->left) {
            current = current->left;
        }
    }
    else if (current !=nullptr ) {
        Node* tmp = this->current->parent;
        if(tmp != nullptr) {
            while(tmp->node_data.first < current->node_data.first) {
                tmp = tmp->parent;
                if(tmp == nullptr)
                    break;
            }
        }
        current = tmp;
    }
    return *this;
  }

  ConstIterator operator++(int)
  {
    Node* return_value = current;
    operator++();
    return ConstIterator(*owner, return_value);
  }

  ConstIterator& operator--()
  {
    if( *this == (*owner).begin() ) {
        throw std::out_of_range("Error! You're gonna to leave to outer space! (Can't decrease)");
    }
    if( !current ) {
        current = ((*owner).findMax((*owner).root)).current;
    }
    else if(current->left) {
        current = current->left;
        while(current->right) {
            current = current->right;
        }
    }
    else if( current->parent && current == current->parent->right ) {
        current = current->parent;
    }
    else {
        while ( current == current->parent->left ) {
            current = current->parent;
        }
        if( current->parent == nullptr ) {
            throw std::out_of_range("Error! You're gonna to leave to outer space! (Can't decrease)");
        }
        current = current->parent;
    }
    return (ConstIterator&)(*this);
  }

  ConstIterator operator--(int)
  {
    Node* return_value = current;
    operator++();
    ConstIterator return_iterator = ConstIterator(*owner, return_value);
    return return_iterator;
  }

  reference operator*() const
  {
  if( !current ) {
    throw std::out_of_range("Oh sh... You're going to dereference that? It's end iterator, man!");
  }
    return current->node_data;
  }

  pointer operator->() const
  {
    return &this->operator*();
  }

  bool operator==(const ConstIterator& other) const
  {
//    bool return_value = ( owner == other.owner && current == other.current ) ? true : false;
    return ( owner == other.owner && current == other.current ) ;
  }

  bool operator!=(const ConstIterator& other) const
  {
    return !(*this == other);
  }

  protected:
    const TreeMap<KeyType, ValueType> *owner;
    Node *current;

    friend class TreeMap<KeyType, ValueType>;
};

template <typename KeyType, typename ValueType>
class TreeMap<KeyType, ValueType>::Iterator : public TreeMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename TreeMap::reference;
  using pointer = typename TreeMap::value_type*;

  explicit Iterator( const TreeMap<KeyType, ValueType> & source, Node *p = nullptr )
        : ConstIterator( source, p ) {}

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

#endif /* AISDI_MAPS_MAP_H */
