#include <iostream>

#include "List.h"
#include "Unordered_map.h"
#include "frequency_dictionary.h"

#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]) {
//    if (argc != 2) {
//        return -1;
//    }
//    std::ifstream file(argv[1]);
//    if (!file.is_open()) {
//        return -1;
//    }
//    std::string new_word;
//    frequency_dictionary dictionary;
//    while (file >> new_word)
//        dictionary.insert(new_word);
//    dictionary.print_three_most_popular_words();
//

//  test dictionary without file;

    frequency_dictionary dictionary;
    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss (str);
    std::string word;
    while (ss >> word)
        dictionary.insert(word);

//    dictionary.print_number_word_copies();
//    std::cout << "_____\n";
//    dictionary.print_reverse_number_word_copies();
//    std::cout << "_____\n";
    dictionary.print_three_most_popular_words();
    return 0;
}
