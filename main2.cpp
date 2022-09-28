#include <iostream>

#include "list.h"
#include "Unordered_map.h"
#include <list>

struct Person {
    std::string name;
    int age;
};

//int main() {
//    list<Person> list;
//    list.push_front({"Bogdan", 22});
//    list.push_front({"Daniil", 23});

int main(int argc, char *argv[]) {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_front(3);
    for (auto k : l) {
        std::cout << k << ' ';
    }
    std::cout << std::endl;
    unordered_map<int, list<std::string>> map;
    map[1].push_back("hello");
    map[1].push_back("by");
    map[1].push_back("good");
    return 0;
}