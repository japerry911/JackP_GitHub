#include "WordList.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <random>

std::vector<std::string> read_words_from_file(const std::string &filename) {
    std::vector<std::string> words;

    std::ifstream in(filename);

    // Ensure file opened
    if (!in.is_open()) {
        throw std::runtime_error("File not found: " + filename);
    }

    // Read file word by word
    while (!in.eof()) {
        std::string word;
        in >> word;
        words.push_back(word);
    }

    in.close();

    return words;
}

std::vector<std::string> filter_words_by_length(const std::vector<std::string> &words, std::string::size_type length) {
    // Copy only the words that are of the specified length
    std::vector<std::string> filtered;
    std::copy_if(words.begin(), words.end(), std::back_inserter(filtered),
                 [length](const std::string &word) { return word.length() == length; });
    return filtered;
}

std::vector<std::string> random_sample(const std::vector<std::string> &list, int size) {
    // If we don't have enough inputs elements, use the whole list
    if (list.size() <= size) {
        return list;
    }

    // This is known as algorithm R and performs reservoir sampling
    // It will select a subset of size size from list with uniform probability
    std::vector<std::string> sample;

    // Copy over size elements to start
    std::copy_n(list.begin(), size, std::back_inserter(sample));

    // Select from the remaining elements with decreasing probability
    std::random_device seed;
    std::mt19937 prng{seed()};
    for (std::vector<std::string>::size_type i = size, e = list.size(); i < e; ++i) {
        std::uniform_int_distribution<std::vector<std::string>::size_type> dist(0, i);
        std::vector<std::string>::size_type idx = dist(prng);
        if (idx < size) {
            sample[idx] = list[i];
        }
    }

    return sample;
}


