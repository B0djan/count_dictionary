#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include "List.h"
#include "Pair.h"
#include "Vector.h"
#include "String.h"

#include <iostream>

namespace my {
    template <class Key, class Value>
    class unordered_map {
    public:
        unordered_map();
        ~unordered_map();

        Value& operator[] (const Key& key);
        void erase(const Key& key);
        void print();
        int size() const;

        my::vector<my::list<my::pair<Key, Value>>>& get_table_data();

    private:
        my::vector<my::list<my::pair<Key, Value>>> table;
        int map_size;

        static int const _table_capacity = 100001;
        static int const _base       = 123;
        static int const _hash_cfA   = 930310127;
        static int const _hash_cfB   = 935489;

        size_t map_hash (const my::string& str) const;
        size_t map_hash (int key) const;
        size_t get_basket_number(int hash) const;
    };

    template <class Key, class Value>
    int unordered_map<Key, Value>::size() const {
        return map_size;
    }

    template <class Key, class Value>
    unordered_map<Key, Value>::unordered_map() : map_size(0) {
        table.resize(_table_capacity);
    }

    template <class Key, class Value>
    unordered_map<Key, Value>::~unordered_map() = default;

    template< typename Key, typename Value >
    size_t unordered_map<Key, Value>::map_hash(const my::string& str) const {
        size_t hash = 0;
        for (auto ch : str)
            hash = (hash * _base + static_cast<size_t>(ch) );
        return hash;
    }

    template< typename Key, typename Value >
    size_t unordered_map<Key, Value>::map_hash(int key) const {
        return (size_t(key) * _hash_cfA) % _hash_cfB;
    }

    template< typename Key, typename Value >
    size_t unordered_map<Key, Value>::get_basket_number(int hash) const {
        return size_t(hash) % size_t(_table_capacity);
    }

    template <class Key, class Value>
    Value& unordered_map<Key, Value>::operator[] (const Key& key) {
        int basket_number = get_basket_number(map_hash(key));
        auto& list = table[basket_number];
        for (auto& e : list) {
            if (e.first == key)
                return e.second;
        }
        list.push_front({key, Value{}});
        map_size += 1;
        return list.begin()->set_value();
    }

    template <class Key, class Value>
    void unordered_map<Key, Value>::erase (const Key& key) {
        int basket_number = get_basket_number(map_hash(key));
        auto& list = table[basket_number];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->first == key) {
                map_size -= 1;
                list.erase(it);
            }
        }
    }

    template <class Key, class Value>
    void unordered_map<Key, Value>::print() {
        for (const auto& e : table) {
            for (const auto& l : e) {
                std::cout << l.first << ' ' << l.second << '\n';
            }
        }
    }

    template<class Key, class Value>
    vector<my::list<my::pair<Key, Value>>> &unordered_map<Key, Value>::get_table_data() {
        return table;
    }
}


//class iterator {
//public:
//    friend class unordered_map<Key, Value>;
//    friend class pair<Key, Value>;
//    using pointer = pair<Key, Value>*;
//    using reference = pair<Key, Value>&;
//
//private:
//    pair<Key, Value>* cur;
//};

//// iterator();
//iterator(pair<Key, Value>* ptr = nullptr);
//iterator(const iterator&);
//iterator& operator=(const iterator&);
//
//iterator& operator++();
//iterator operator++(int);
//reference operator*() const;
//pointer operator->() const;
//iterator& operator--();
//iterator operator--(int);
//
//bool operator==(iterator other) const;
//bool operator!=(iterator other) const;

//    template <class Key, class Value>
//    unordered_map<Key, Value>::iterator::iterator(pair<Key, Value>* ptr) : cur{ptr} {}
//
//
//    template <class Key, class Value>
//    unordered_map<Key, Value>::iterator::iterator(const iterator& other) : cur{other.cur} {}
//
//    template <class Key, class Value>
//    typename unordered_map<Key, Value>::iterator& unordered_map<Key, Value>::iterator::operator=(
//            const unordered_map::iterator& other) {
//        cur = other.cur;
//        return *this;
//    }
//
//    template <class Key, class Value>
//    typename unordered_map<Key, Value>::iterator& unordered_map<Key, Value>::iterator::operator++() {
//        cur = cur->next;
//        return *this;
//    }
//
//    template <class Key, class Value>
//    typename unordered_map<Key, Value>::iterator& unordered_map<Key, Value>::iterator::operator--() {
//        cur = cur->prev;
//        return *this;
//    }
//
//    template <class Key, class Value>
//    typename unordered_map<Key, Value>::iterator::reference unordered_map<Key, Value>::iterator::operator*() const {
//        return cur;
//    }
//
//    template <class Key, class Value>
//    typename unordered_map<Key, Value>::iterator::pointer unordered_map<Key, Value>::iterator::operator->() const {
//        return &cur;
//    }
//
//    template <class Key, class Value>
//    bool unordered_map<Key, Value>::iterator::operator==(iterator other) const {
//        return other.cur == cur;
//    }
//
//    template <class Key, class Value>
//    bool unordered_map<Key, Value>::iterator::operator!=(iterator other) const {
//        return other.cur != cur;
//    }
//























// namespace my

//namespace my {
//    template <class Key, class Value>
//    class unordered_map {
//    public:
//        struct pair {
//            friend class unordered_map<Key, Value>;
//            pair(const Key& key, const Value& value);
//            Key key;
//            Value value;
//            pair* prev;
//            pair* next;
//        };
//        class iterator {
//        public:
//            friend class unordered_map<Key, Value>;
//            using pointer = Value*;
//            using reference = Value&;
//
//            // iterator();
//            iterator(pair* ptr = nullptr);
//            iterator(const iterator&);
//            iterator& operator=(const iterator&);
//
//            iterator& operator++();
//            reference operator*() const;
//            pointer operator->() const;
//            iterator& operator--();
//
//            bool operator==(iterator other) const;
//            bool operator!=(iterator other) const;
//
//        private:
//            pair* cur;
//        };
//        class const_iterator {
//        public:
//            friend class unordered_map<Key, Value>;
//            using pointer = const Value*;
//            using reference = const Value&;
//
//            const_iterator(pair* ptr = nullptr);
//            const_iterator(const iterator&);
//            const_iterator& operator=(const iterator&);
//
//            const_iterator& operator++();
//            reference operator*() const;
//            pointer operator->() const;
//            const_iterator& operator--();
//
//            bool operator==(const_iterator other) const;
//            bool operator!=(const_iterator other) const;
//
//        private:
//            pair* cur;
//        };
//
//        unordered_map();
//        ~unordered_map();
//
//        Value& operator[] (const Key& key);
//        void erase (const Key& key);
//
//        iterator begin() const;
//        iterator end() const;
//
//        bool empty() const;
//        size_t size() const;
//
//    private:
//        pair* last_ptr;
//        pair* first_ptr;
//        size_t unordered_map_size;
//
//        static int const _table_size = 7;
//        static int const _base       = 123;
//        static int const _hash_cfA   = 930310127;
//        static int const _hash_cfB   = 935489;
//
//        int map_hash (const std::string& str) const;
//        int map_hash (int key) const ;
//    };
//
//    template <class T>
//    list<T>::iterator::iterator(pair* ptr) : cur{ptr} {}

//}  // namespace my



/*
#include <vector>
#include <algorithm>
#include <list>
#include <cmath>
#include <stdexcept>

constexpr static char NO_ELEMENT_VALUE = '.';
constexpr static char EXIST_ELEMENT_VALUE = '+';
constexpr static char DELETED_ELEMENT_VALUE = '-';

template<class KeyType, class ValueType>
class HashMap {
private:
    using listElement = my::pair<const KeyType, ValueType>;

    std::vector<my::pair<typename my::list<listElement>::iterator, char>> table_;
    my::list<listElement> elements_;
    size_t size_ = 0;
    size_t step_ = 1;

public:
    using iterator = typename std::list<listElement>::iterator;
    using const_iterator = typename std::list<listElement>::const_iterator;

    HashMap(const Hash& hash = Hash()) : hasher_(hash) {
        table_.resize(2, {iterator(), NO_ELEMENT_VALUE});
    }

    template<typename Iterator>
    HashMap(Iterator first, Iterator last, const Hash& hash = Hash()) : hasher_(hash) {
        table_.resize(std::distance(first, last) * 2, {iterator(), NO_ELEMENT_VALUE});
        while (first != last) {
            insert(*first++);
        }
    }

    HashMap(std::initializer_list<std::pair<KeyType, ValueType>> ilist, const Hash& hash = Hash()) {
        *this = HashMap(ilist.begin(), ilist.end(), hash);
    }

    HashMap(size_t size, const Hash& hash = Hash()) : hasher_(hash) {
        table_.resize(size, {iterator(), NO_ELEMENT_VALUE});
    }

    HashMap(const HashMap&) = default;

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    Hash hash_function() const {
        return hasher_;
    }

    void insert(const std::pair<KeyType, ValueType>& element) {
        auto bucketIndex = hasher_(element.first) % table_.size();
        while (table_[bucketIndex].second != NO_ELEMENT_VALUE) {
            if (table_[bucketIndex].second == EXIST_ELEMENT_VALUE &&
                table_[bucketIndex].first->first == element.first)
                return;
            bucketIndex += step_;
            if (bucketIndex >= table_.size()) {
                bucketIndex %= table_.size();
            }
        }

        size_++;

        bucketIndex = hasher_(element.first) % table_.size();
        while (table_[bucketIndex].second == EXIST_ELEMENT_VALUE) {
            bucketIndex += step_;
            if (bucketIndex >= table_.size()) {
                bucketIndex %= table_.size();
            }
        }
        elements_.push_back(element);

        auto last = elements_.end();
        --last;
        table_[bucketIndex] = make_pair(last, EXIST_ELEMENT_VALUE);

        if (size_ * 2 > table_.size()) {
            rehash(table_.size() * 2);
        }
    }

    void erase(KeyType key) {
        auto bucketIndex = hasher_(key) % table_.size();
        while (table_[bucketIndex].second != NO_ELEMENT_VALUE) {
            if (table_[bucketIndex].second == EXIST_ELEMENT_VALUE &&
                            table_[bucketIndex].first->first == key) {
                size_--;
                table_[bucketIndex].second = DELETED_ELEMENT_VALUE;
                elements_.erase(table_[bucketIndex].first);
                if (size_ * 4 <= table_.size()) {
                    rehash(table_.size() / 2);
                }
                return;
            }
            bucketIndex += step_;
            if (bucketIndex >= table_.size()) {
                bucketIndex %= table_.size();
            }
        }
    }

    void rehash(size_t newSize) {
        HashMap<KeyType, ValueType, Hash> new_table(newSize, hasher_);
        for (auto i : elements_) {
            new_table.insert(i);
        }

        std::swap(table_, new_table.table_);
        std::swap(elements_, new_table.elements_);
        std::swap(size_, new_table.size_);
        std::swap(step_, new_table.step_);
    }

    iterator begin() {
        return elements_.begin();
    }

    iterator end() {
        return elements_.end();
    }

    const_iterator begin() const {
        return elements_.cbegin();
    }

    const_iterator end() const {
        return elements_.cend();
    }

    iterator find_position(KeyType key) const {
        auto bucketIndex = hasher_(key) % table_.size();
        while (table_[bucketIndex].second != NO_ELEMENT_VALUE) {
            if (table_[bucketIndex].second == EXIST_ELEMENT_VALUE &&
                (*table_[bucketIndex].first).first == key) {
                return table_[bucketIndex].first;
            }
            bucketIndex += step_;
            if (bucketIndex >= table_.size()) {
                bucketIndex %= table_.size();
            }
        }
        return iterator{};
    }

    iterator find(KeyType key) {
        auto position = find_position(key);
        return position == iterator{} ? end() : position;
    }

    const_iterator find(KeyType key) const {
        auto position = find_position(key);
        return position == iterator{} ? end() :
                            static_cast<const_iterator>(position);
    }

    ValueType& operator[](KeyType key) {
        auto position = find(key);
        if (position != end()) {
            return position->second;
        }
        insert(std::make_pair(key, ValueType{}));
        auto last = elements_.end();
        --last;
        return (*last).second;
    }

    const ValueType& at(KeyType key) const {
        auto position = find(key);
        if (position != end()) {
            return position->second;
        }
        throw std::out_of_range("error");
    }

    void clear() {
        elements_.clear();
        table_.clear();
        size_ = 0;
        table_.resize(2, {iterator(), NO_ELEMENT_VALUE});
    }

    HashMap& operator=(HashMap new_table) {
        std::swap(table_, new_table.table_);
        std::swap(elements_, new_table.elements_);
        std::swap(size_, new_table.size_);
        std::swap(step_, new_table.step_);
        return *this;
    }
};

*/

/*
template< typename First, typename Second > class pair;
template< typename Key, typename Value >    class Unordered_map;
template< typename Key, typename Value >    class unordered_map_const_iterator;
template< typename Key, typename Value >    class unordered_map_iterator;


template< typename First, typename Second >
class pair {
public:
    First _first;
    Second _second;
    pair* _next;
    pair* _prev;

    explicit pair() = default;
    explicit pair(const First& first) : _first(first) , _next(nullptr), _prev(nullptr) {
        _second = Second();
    };
    explicit pair(const First& first, Second& second):
            _first(first), _second(second), _next(nullptr), _prev(nullptr)  {};

    Second& second() { return _second; }
    First first() const { return _first; }
    Second second() const { return _second; }
};

template < typename Key, typename Value >
class Unordered_map {
public:
    my::list< pair<Key, Value> > * _baskets;
    pair<Key, Value>* _head_ptr = nullptr;
    pair<Key, Value>* _tail_ptr = nullptr;

    size_t _size = 0;

    static int const _table_size = 7;
    static int const _base       = 123;
    static int const _hash_cfA   = 930310127;
    static int const _hash_cfB   = 935489;

    int map_hash (const std::string& str) const;
    int map_hash (size_t key) const ;
    int map_hash (int key) const;

    size_t get_basket_number(size_t hash) const;
public:
    using const_iterator =  ::unordered_map_iterator<Key, Value>;
    using iterator =        ::unordered_map_const_iterator<Key, Value>;

    explicit Unordered_map();
    ~Unordered_map();

    Value& operator[] (const Key& key);
    void erase (const Key& key);

    const_iterator begin() const {
        iterator it;
        it._current = _head_ptr;
        return it;
    }

    const_iterator end() const {
        const_iterator it;
        if (_tail_ptr)
            it._current = _tail_ptr->_next;
        return it;
    }

    iterator begin() {
        iterator it;
        it._current = _head_ptr;
        return it;
    }

    iterator end() {
        iterator it;
        if (_tail_ptr)
            it._current = _tail_ptr->_next;
        return it;
    }
};

template< typename Key, typename Value >
Unordered_map<Key, Value>::Unordered_map() {
    _baskets = new my::list<pair<Key, Value>>[_table_size];
}

template< typename Key, typename Value >
Unordered_map<Key, Value>::~Unordered_map() {
    delete[] _baskets;
}

template< typename Key, typename Value >
Value& Unordered_map<Key, Value>::operator[] (const Key& key) {
    size_t idx = get_basket_number(map_hash(key));
    auto &list = _baskets[idx];
    for (auto& it : list)
        if (it.first() == key) {
            return it.second();
        }
    auto new_pair_ptr = list.push_front(pair<Key, Value> (key));
    new_pair_ptr->_prev = _tail_ptr;
    if (_tail_ptr)
        _tail_ptr->_next = new_pair_ptr;
    _tail_ptr = new_pair_ptr;
    if (!_head_ptr)
        _head_ptr = new_pair_ptr;
    _size += 1;
    return new_pair_ptr->second();
}

template< typename Key, typename Value >
void Unordered_map<Key, Value>::erase(const Key& key) {
    size_t idx = get_basket_number(map_hash(key));
    auto &list = _baskets[idx];
    for (auto& it : list)
        if (it.first() == key) {
            if (it._prev)
                it._prev->_next = it._next;
            if (it._next)
                it._next->_prev = it._prev;
            if (_head_ptr == &it)
                _head_ptr = (it._next);
            if (_tail_ptr == &it)
                _tail_ptr = (it._prev);
        }
    _size -= 1;
}

template< typename Key, typename Value >
int Unordered_map<Key, Value>::map_hash(const std::string& str) const{
    int hash = 0;
    for (auto ch : str)
        hash = (hash * _base + static_cast<int>(ch) );
    return hash;
}

template< typename Key, typename Value >
int Unordered_map<Key, Value>::map_hash(int key) const{
    return (key * _hash_cfA) % _hash_cfB;
}

template<typename Key, typename Value>
int Unordered_map<Key, Value>::map_hash(size_t key) const {
    return ((int)key * _hash_cfA) % _hash_cfB;
}

template< typename Key, typename Value >
size_t Unordered_map<Key, Value>::get_basket_number(size_t hash) const{
    return hash % _table_size;
}

template < typename Key, typename Value >
class unordered_map_const_iterator {
public:
    pair<Key, Value>* _current;
public:
    friend class unordered_map<Key, Value>;
    unordered_map_const_iterator() : _current(nullptr) {};

    virtual const pair<Key, Value>& operator*() const {
        return (*_current);
    }

    virtual unordered_map_const_iterator& operator++() {
        if (_current)
            _current = _current->_next;
        return *this;
    }

    bool operator==(const unordered_map_const_iterator& rhs) const {
        return _current == rhs._current;
    }

    bool operator!= (const unordered_map_const_iterator& rhs) const {
        return _current != rhs._current;
    }

    pair<Key, Value>* operator->() {
        return _current;
    }
};

template < typename Key, typename Value >
class unordered_map_iterator : public unordered_map_const_iterator<Key, Value> {
public:
    friend class unordered_map<Key, Value>;

    pair<Key, Value>& operator*() {
        return unordered_map_iterator<Key, Value>::_current->_node;
    }

    const pair<Key, Value>& operator*() const {
        return unordered_map_iterator<Key, Value>::operator*();
    }

    unordered_map_iterator& operator++() {
        unordered_map_iterator<Key, Value>::_current = unordered_map_iterator<Key, Value>::_current->_next;
        return *this;
    }
};

*/

#endif
