#ifndef FREQUENCY_DICTIONARY_H
#define FREQUENCY_DICTIONARY_H

#include "Unordered_map.h"
#include "String.h"

class frequency_dictionary {
private:
    my::unordered_map<my::string, int> _string_to_number;
    my::unordered_map<int, my::list<my::string>> _number_to_string;
    my::string* _free_most_popular_words;
    const char* punctuation_marks = ".,!?:";

    bool parse_word(my::string str, my::string& parsed_word);
public:
    explicit frequency_dictionary() { _free_most_popular_words = new my::string[3]; }
    ~frequency_dictionary() { delete[] _free_most_popular_words; }
    void fill();

    void insert(const my::string& word);
    void insert(const my::string& word, int value);
    int  search(const my::string& word);
    void erase (const my::string& word);

    void print_three_most_popular_words();
    void print_number_word_copies();
};

bool frequency_dictionary::parse_word(my::string str, my::string& parsed_word) {
    if (str.empty())
        return false;
    int end_offset = 0;
    bool punctuation = true;
    for (int i = (int)str.size() - 1; i >= 0 && punctuation; i--, end_offset++) {
        punctuation = false;
        for (const char* ptr = punctuation_marks; *ptr; ptr++)
            punctuation = punctuation || (*ptr == str[i]);
    }
    for (int i = 0; i < (int)str.size() - end_offset; ++i) {
        str[i] = (char)tolower(str[i]);
        if (!(str[i] >= 'a' && str[i] <= 'z'))
            return false;
    }
    parsed_word = my::string(str.begin(), str.end()-end_offset + 1);
    return true;
}

void frequency_dictionary::insert(const my::string& word) {
    my::string parsed_word;
    if (parse_word(word, parsed_word))
        _string_to_number[parsed_word] += 1;
}

void frequency_dictionary::insert(const my::string& word, int value) {
    my::string parsed_word;
    if (parse_word(word, parsed_word))
        _string_to_number[parsed_word] += value;
}

int frequency_dictionary::search(const my::string& word) {
    std::string parsed_word;
    if (!parse_word(word, parsed_word))
        return -1;
    return _string_to_number[parsed_word];
}

void frequency_dictionary::erase(const my::string& word) {
    _string_to_number.erase(word);
}

void frequency_dictionary::fill() {

    for (const auto& e: _string_to_number.get_table_data()) {
        for (const auto& p : e) {
            _number_to_string[p.second].push_back(p.first);
        }
    }

    int positions[3] = {-1, -1, -1};
    for (const auto& e: _number_to_string.get_table_data()) {
        for (const auto& p : e) {
            if (p.first > positions[0]) {
                positions[2] = positions[1];
                positions[1] = positions[0];
                positions[0] = p.first;
                continue;
            }
            if (p.first > positions[1]) {
                positions[2] = positions[1];
                positions[1] = p.first;
                continue;
            }
            if (p.first > positions[2]) {
                positions[2] = p.first;
                continue;
            }
        }
    }

    int i = 0;
    for (int& position : positions) {
        if (i >= 3 && position != -1)
            return;
        for (const auto& l : _number_to_string[position]) {
            if (i >= 3 && position != -1)
                return;
            _free_most_popular_words[i++] = l;
        }
    }
}

void frequency_dictionary::print_three_most_popular_words() {
    if (!_number_to_string.size())
        fill();
    std::cout << "print three most popular words:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        if (_free_most_popular_words[i].empty()) {
            std::cout << '\n';
            return;
        }
        std::cout << _free_most_popular_words[i] << ' ';
    }
    std::cout << '\n';
}

void frequency_dictionary::print_number_word_copies() {
    std::cout << "print number word copies:" << std::endl;
    for (const auto& l : _string_to_number.get_table_data()) {
        for (const auto& p : l) {
            std::cout << '{' << p.first << ' ' << p.second << '}' << ",\n";
        }
    }
}


#endif //  FREQUENCY_DICTIONARY_H
