#ifndef LIST_H
#define LIST_H

namespace my {

    template <class T>
    class list {
    public:
        class const_iterator;
        struct node {
            friend class list<T>;
            node(const T& value);
            T data;
            node* prev;
            node* next;
        };
        class iterator {
        public:
            friend class list<T>;
            using pointer = T*;
            using reference = T&;

            // iterator();
            iterator(node* ptr = nullptr);
            iterator(const iterator&);
            iterator& operator=(const iterator&);

            iterator& operator++();
            iterator operator++(int);
            reference operator*() const;
            pointer operator->() const;
            iterator& operator--();
            iterator operator--(int);

            bool operator==(iterator other) const;
            bool operator!=(iterator other) const;

        private:
            node* cur;
        };

        class const_iterator {
        public:
            friend class list<T>;
            using pointer = const T*;
            using reference = const T&;

            const_iterator(node* ptr = nullptr);
            const_iterator(const const_iterator&);
            const_iterator(const iterator&);
            const_iterator& operator=(const const_iterator&);

            const_iterator& operator++();
            const_iterator operator++(int);
            reference operator*() const;
            pointer operator->() const;
            const_iterator& operator--();
            const_iterator operator--(int);

            bool operator==(const_iterator other) const;
            bool operator!=(const_iterator other) const;

        private:
            node* cur;
        };

        list();
        ~list();

        list(const list& other);

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

        iterator begin() const;
        iterator end() const;

        bool empty() const;
        int size() const;
        void clear();

        void push_back(const T& value);
        void pop_back();

        void push_front(const T& value);
        void pop_front();

        const_iterator erase(const_iterator pos);

    private:
        node* last_ptr;
        node* first_ptr;
        int list_size;
    };

    template <class T>
    list<T>::iterator::iterator(node* ptr) : cur(ptr) {}

    template <class T>
    list<T>::iterator::iterator(const iterator& other) : cur{other.cur} {}

    template <class T>
    typename list<T>::iterator& list<T>::iterator::operator=(
            const iterator& other) {
        cur = other.cur;
        return *this;
    }

    template <class T>
    typename list<T>::iterator& list<T>::iterator::operator++() {
        cur = cur->next;
        return *this;
    }

    template <class T>
    typename list<T>::iterator& list<T>::iterator::operator--() {
        cur = cur->prev;
        return *this;
    }

    template <class T>
    typename list<T>::iterator list<T>::iterator::operator++(int) {
        node* tmp = cur;
        const_iterator it(tmp);
        cur = cur->next;
        return it;
    }

    template <class T>
    typename list<T>::iterator list<T>::iterator::operator--(int) {
        node* tmp = cur;
        const_iterator it(tmp);
        cur = cur->prev;
        return it;
    }

    template <class T>
    typename list<T>::iterator::reference list<T>::iterator::operator*() const {
        return cur->data;
    }

    template <class T>
    typename list<T>::iterator::pointer list<T>::iterator::operator->() const {
        return &cur->data;
    }

    template <class T>
    bool list<T>::iterator::operator==(iterator other) const {
        return other.cur == cur;
    }

    template <class T>
    bool list<T>::iterator::operator!=(iterator other) const {
        return other.cur != cur;
    }

    template <class T>
    list<T>::const_iterator::const_iterator(const iterator& other)
            : cur{other.cur} {}

    template <class T>
    list<T>::const_iterator::const_iterator(node* ptr) : cur{ptr} {}

    template <class T>
    list<T>::const_iterator::const_iterator(const const_iterator& other)
            : cur{other.cur} {}

    template <class T>
    typename list<T>::const_iterator& list<T>::const_iterator::operator=(
            const const_iterator& other) {
        cur = other.cur;
        return *this;
    }

    template <class T>
    typename list<T>::const_iterator& list<T>::const_iterator::operator++() {
        cur = cur->next;
        return *this;
    }

    template <class T>
    typename list<T>::const_iterator list<T>::const_iterator::operator++(int) {
        node* tmp = cur;
        const_iterator it(tmp);
        cur = cur->next;
        return it;
    }

    template <class T>
    typename list<T>::const_iterator& list<T>::const_iterator::operator--() {
        cur = cur->prev;
        return *this;
    }

    template <class T>
    typename list<T>::const_iterator list<T>::const_iterator::operator--(int) {
        node* tmp = cur;
        const_iterator it(tmp);
        cur = cur->prev;
        return it;
    }

    template <class T>
    typename list<T>::const_iterator::reference list<T>::const_iterator::operator*()
    const {
        return cur->data;
    }

    template <class T>
    typename list<T>::const_iterator::pointer list<T>::const_iterator::operator->()
    const {
        return &cur->data;
    }

    template <class T>
    bool list<T>::const_iterator::operator==(const_iterator other) const {
        return other.cur == cur;
    }

    template <class T>
    bool list<T>::const_iterator::operator!=(const_iterator other) const {
        return other.cur != cur;
    }

    template <class T>
    typename list<T>::iterator list<T>::begin() const {
        if (first_ptr == nullptr) return iterator();

        iterator it(first_ptr);
        return it;
    }

    template <class T>
    typename list<T>::iterator list<T>::end() const {
        if (last_ptr == nullptr) return iterator();

        iterator it(last_ptr->next);
        return it;
    }

    template <class T>
    list<T>::node::node(const T& value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }

    template <class T>
    list<T>::list() {
        first_ptr = nullptr;
        last_ptr = nullptr;
        list_size = 0;
    }

    template <class T>
    void list<T>::push_back(const T& value) {
        if (list_size == 0) {
            first_ptr = new node(value);
            node* cap = new node(T{});
            first_ptr->next = cap;
            cap->next = nullptr;
            cap->prev = first_ptr;

            last_ptr = first_ptr;
        } else {
            node* new_node = new node(value);
            last_ptr->next->prev = new_node;
            new_node->next = last_ptr->next;
            new_node->prev = last_ptr;
            last_ptr->next = new_node;
            last_ptr = new_node;
        }
        list_size++;
    }

    template <class T>
    void list<T>::push_front(const T& value) {
        if (list_size == 0) {
            first_ptr = new node(value);
            node* cap = new node(T{});
            first_ptr->next = cap;
            cap->next = nullptr;
            cap->prev = first_ptr;
            last_ptr = first_ptr;
        } else {
            node* new_node = new node(value);
            first_ptr->prev = new_node;
            new_node->next = first_ptr;
            new_node->prev = nullptr;
            first_ptr = new_node;
        }
        list_size++;
    }

    template <class T>
    void list<T>::pop_front() {
        if (list_size == 0) {
        } else if (list_size == 1) {
            delete first_ptr->next;
            delete first_ptr;
            first_ptr = nullptr;
            last_ptr = nullptr;
        } else {
            first_ptr = first_ptr->next;
            delete first_ptr->prev;
            first_ptr->prev = nullptr;
        }
        list_size--;
    }

    template <class T>
    void list<T>::pop_back() {
        if (list_size == 0) {
        } else if (list_size == 1) {
            delete first_ptr->next;
            delete first_ptr;
            first_ptr = nullptr;
            last_ptr = nullptr;
        } else {
            node* tmp = last_ptr->prev;
            last_ptr->prev->next = last_ptr->next;
            last_ptr->next->prev = last_ptr->prev;
            delete last_ptr;
            last_ptr = tmp;
        }
        list_size--;
    }

    template <class T>
    typename list<T>::const_iterator list<T>::erase(const_iterator pos) {
        if (list_size == 1) {
            pop_back();
            return iterator();
        }
        list_size--;
        if (pos == begin()) {
            first_ptr = pos.cur->next;
            delete pos.cur;
            first_ptr->prev = nullptr;
            return const_iterator(first_ptr);
        }

        auto it_res = const_iterator(pos.cur->next);
        pos.cur->prev->next = pos.cur->next;
        pos.cur->next->prev = pos.cur->prev;
        if (pos == const_iterator(last_ptr)) last_ptr = last_ptr->prev;
        delete pos.cur;
        return it_res;
    }

    template <class T>
    T& list<T>::front() {
        return first_ptr->data;
    }

    template <class T>
    const T& list<T>::front() const {
        return first_ptr->data;
    }

    template <class T>
    T& list<T>::back() {
        return last_ptr->data;
    }

    template <class T>
    const T& list<T>::back() const {
        return last_ptr->data;
    }

    template <class T>
    list<T>::~list() {
        node* cur = first_ptr;
        node* next;
        for (; cur; cur = next) {
            next = cur->next;
            delete cur;
        }
    }

    template <class T>
    list<T>::list(const list& other) : list() {
        for (const auto& elem : other) {
            push_back(elem);
        }
    }

    template <class T>
    bool list<T>::empty() const {
        return list_size == 0;
    }

    template <class T>
    int list<T>::size() const {
        return list_size;
    }

    template <class T>
    void list<T>::clear() {
        while (list_size) pop_front();
    }

}  // namespace my

#endif
