#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <cassert>

namespace my {
    class string {
    public:
        class iterator {
        public:
            using pointer = const char*;
            using reference = const char&;

            // iterator();
            explicit iterator(const char* ptr = nullptr);
            iterator(const iterator&);
            iterator& operator=(const iterator&);

            iterator& operator++();
            reference operator*() const;
            pointer operator->() const;

            bool operator==(const iterator& other) const;
            bool operator!=(iterator other) const;
        private:
            const char* cur;
        };
    public:

        string();
        explicit string(const char* s);
        string(const my::string::iterator& it_begin, const my::string::iterator& it_end);
        string (const string& other);
        ~string();

        const char& at(int i);
        int size() const;
        bool empty() const;

        iterator begin() const;
        iterator end() const;
    private:
        int _size{};
        const char* _data{};
    };

    string::iterator::iterator(const char *ptr) : cur(ptr) {}

    string::iterator::iterator(const string::iterator& other) : cur{other.cur} {}

    string::iterator &string::iterator::operator=(const iterator& other) {
        cur = other.cur;
        return *this;
    }

    string::iterator &string::iterator::operator++() {
        cur += 1;
        return *this;
    }

    const char &string::iterator::operator*() const {
        return *cur;
    }

    string::iterator::pointer string::iterator::operator->() const {
        return cur;
    }

    bool string::iterator::operator==(const string::iterator& other) const {
        return other.cur == cur;
    }

    bool string::iterator::operator!=(string::iterator other) const {
        return other.cur != cur;
    }

    typename string::iterator string::begin() const {
        if (_data == nullptr) return iterator();

        iterator it(_data);
        return it;
    }

    typename string::iterator string::end() const {
        if (_data == nullptr) return iterator();

        iterator it(&_data[_size]);
        return it;
    }

    string::string() : _size(0), _data(nullptr) {};
    string::string(const my::string::iterator& it_begin, const my::string::iterator& it_end) {
        char* tmp = new char[*it_end - *it_begin];
        int i = 0;
        while (it_begin != it_end) {
            tmp[i] = *it_begin ;
            i += 1;
        }
        _data = tmp;
    }
    string::string(const char* s) : _size(s ? int(strlen(s)) : 0), _data(s) {};
    string::string(const string& other) : _size(other._size) {
        char *tmp = new char[other._size + 1];
        for (int i = 0; i <= _size; ++i) {
            tmp[i] = other._data[i];
        }
        _data = tmp;
    }

    string::~string() {
        delete[] _data;
    }

    const char &string::at(int i) {
        assert(i >= 0);
        assert(i < _size);
        return _data[i];
    }

    int string::size() const {
        return _size;
    }

    bool string::empty() const {
        return _size == 0;
    }
}

#endif
