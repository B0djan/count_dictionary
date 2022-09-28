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

            friend  std::istream& operator>>(std::istream &in, my::string& str);
            friend  std::ostream& operator<<(std::ostream &in, const my::string& str);

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
        explicit string(char* s);
        string(const my::string::iterator& it_begin, const my::string::iterator& it_end);
        string (const string& other);
        ~string();

        const char& at(int i);
        int size() const;
        bool empty() const;
        char& operator[] (int i);

        iterator begin() const;
        iterator end() const;
    private:
        int _size{};
        int capaity{};
        char* _data{};
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
    string::string(char* s) : _size(s ? int(strlen(s)) : 0), _data(s) {};
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

    char &string::operator[](int i) {
        return _data[i];
    }
}

std::ostream& operator << (std::ostream &os, const my::string& str)
{
    for (const auto c : str) {
        os << c;
    }
    return os;
}

std::istream& operator>>(std::istream &in, my::string& str)
{
    str._capacity = 10;
    str._data = new char[str._capacity];
    str._size = 0;
    int i = 0;
    char c = 0;
    while (c != ' ') {
        if (str._size == str._capacity) {
            str._capacity += 2;
            char* tmp = new char[str._capacity];
            for (int i = 0 ; i <= str.size(); ++i) {
                tmp[i] = str._data[i];
                delete str._data;
                str.data = tmp;
            }
        }
        in.get(c);
        str._data[i] = c;
        i++;
        str._size++;
    }
    return in;
}

#endif
