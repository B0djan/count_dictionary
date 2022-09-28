
#ifndef PAIR_H
#define PAIR_H

namespace my {

    template <class T1, class T2>
    struct pair {

        pair() = default;
        explicit pair(const T1& key) : first(key), second(T2{}) {};
        pair(const T1& key, const T2& value) : first(key), second(value) {};
        pair(const pair<T1, T2>& other) :
            first(other.first), second(other.second) {};
        T2& set_value() {
            return second;
        }

        T1 first;
        T2 second;
    };

}  // namespace my

#endif
