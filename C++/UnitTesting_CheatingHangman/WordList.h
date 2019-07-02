//
// Created by Will Mitchell on 2019-03-31.
//

#ifndef INC_01_UNIT_TESTING_HANGMAN_WORDLIST_H
#define INC_01_UNIT_TESTING_HANGMAN_WORDLIST_H

#include <string>
#include <vector>

std::vector<std::string> read_words_from_file(const std::string &filename);
std::vector<std::string> filter_words_by_length(const std::vector<std::string> &words, std::string::size_type length);
std::vector<std::string> random_sample(const std::vector<std::string> &list, int size);

#endif //INC_01_UNIT_TESTING_HANGMAN_WORDLIST_H
