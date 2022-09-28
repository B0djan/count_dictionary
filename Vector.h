#ifndef VECTOR_H
#define VECTOR_H

#include <unistd.h>

namespace my {

    template<typename T> class vector;

    template<typename T>
    class vector {
        class iterator {
        public:
            friend class vector<T>;
            using pointer = T*;
            using reference = T&;

            // iterator();
            iterator(T* ptr = nullptr);
            iterator(const iterator&);
            iterator& operator=(const iterator&);

            iterator& operator++();
            reference operator*() const;
            pointer operator->() const;
            iterator& operator--();

            bool operator==(iterator other) const;
            bool operator!=(iterator other) const;
        private:
            T* cur;
        };

    public:
        explicit vector();
        explicit vector(size_t init_size, T init_value);

        vector(const vector& other);
        ~vector();

        void push_back(const T& new_element);
        void pop_back();

        iterator begin() const;
        iterator end() const;

        size_t get_size() const;
        size_t get_capacity() const;

        T& operator[] (size_t index);
        const T& operator[] (size_t index) const;
        vector<T>& operator= (const vector<T>& other);

        size_t resize();
        size_t resize(size_t new_size);

    private:
        T* data = nullptr;
        size_t size;
        size_t capacity;
    };

    template <class T>
    vector<T>::iterator::iterator(T* ptr) : cur{ptr} {}

    template <class T>
    vector<T>::iterator::iterator(const iterator& other) : cur{other.cur} {}

    template <class T>
    typename vector<T>::iterator& vector<T>::iterator::operator=(
            const iterator& other) {
        cur = other.cur;
        return *this;
    }

    template <class T>
    typename vector<T>::iterator& vector<T>::iterator::operator++() {
        cur = cur + 1;
        return *this;
    }

    template <class T>
    typename vector<T>::iterator& vector<T>::iterator::operator--() {
        cur -= 1;
        return *this;
    }

    template <class T>
    typename vector<T>::iterator::reference vector<T>::iterator::operator*() const {
        return *cur;
    }

    template <class T>
    typename vector<T>::iterator::pointer vector<T>::iterator::operator->() const {
        return &*cur;
    }

    template <class T>
    bool vector<T>::iterator::operator==(iterator other) const {
        return other.cur == cur;
    }

    template <class T>
    bool vector<T>::iterator::operator!=(iterator other) const {
        return other.cur != cur;
    }

    template <class T>
    typename vector<T>::iterator vector<T>::begin() const {
        if (data == nullptr) return iterator();
        return iterator(&data[0]);
    }

    template <class T>
    typename vector<T>::iterator vector<T>::end() const {
        if (data == nullptr) return iterator();
        return iterator(&data[size]);
    }

    template<typename T>
    vector<T>::vector() : size(0), capacity(1) {
        data = new T[capacity];
    }

    template<typename T>
    vector<T>::vector(size_t init_size, T init_value)
    : size (init_size ), capacity (2 * size ) {
        data = new T[capacity];
        for ( auto i = 0; i < size; ++i )
            data[i] = init_value;
    }

    template<typename T>
    vector<T>::vector(const vector& other) : size (other.size ), capacity (other.capacity ) {
        if (this != &other) {
            delete[] data;
            data = new T[capacity];
            for (auto i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    template<typename T>
    vector<T>::~vector() { delete[] data; }

//    template<typename T>
//    size_t vector<T>::resize() {
//        capacity *= 2;
//        T* new_data = new T[capacity];
//        for ( size_t i = 0; i < size; ++i ) {
//            new_data[i] = data[i];
//        }
//        delete[] data;
//        data = new_data;
//        return capacity;
//    }

    template<typename T>
    size_t vector<T>::resize(size_t new_size) {
        int old_size = size;
        size = new_size;
        capacity = 2 * size;
        T* new_data = new T[capacity];
        for (size_t i = 0; i < old_size; ++i) {
            new_data[i] = data[i];
        }
        for (int i = old_size; i < size; ++i) {
            new_data[i] = T{};
        }
        delete[] data;
        data = new_data;
        return capacity;
    }

    template<typename T>
    size_t vector<T>::get_size() const { return size; }

    template<typename T>
    size_t vector<T>::get_capacity() const { return capacity; }

    template<typename T>
    void vector<T>::push_back(const T& new_element) {
        if (size == capacity)
            resize();
        data[++size - 1] = new_element;
    }

    template<typename T>
    void vector<T>::pop_back() {
        if ( size > 0) {
            size = size - 1;
        }                                                               // or exception
    }

    template<typename T>
    T& vector<T>::operator[] (size_t index) {
        if ( index < 0 && index > size - 1 ) {} // or exception
        return { data[index] };
    }

    template<typename T>
    const T& vector<T>::operator[] (size_t index) const {
        if ( index < 0 && index > size - 1 ) {}  // or exception
        return { data[index] };
    }

    template<typename T>
    vector<T>& vector<T>::operator= (const vector<T>& other) {
        if(this != &other)
        {
            size = other.size;
            capacity = other.capacity;
            delete[] data;
            data = new T[capacity];
            for ( auto i = 0; i < size; ++i ) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

}

#endif
