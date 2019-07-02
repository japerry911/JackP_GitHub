//
// Created by Will Mitchell on 2019-03-31.
//

#ifndef INC_01_UNIT_TESTING_HANGMAN_HANGMAN_H
#define INC_01_UNIT_TESTING_HANGMAN_HANGMAN_H

#include <iostream> // preferable to use this over iostream inside headers
#include <map>
#include <string>
#include <vector>

class Hangman {
public:
    explicit Hangman(std::vector<std::string> word_list, int guesses = 5, bool show_cheating = true);

    enum class game_status { not_over, win, loss };
    game_status status() const;

    enum class guess_validity { valid, incorrect_length, non_letter, repeat_guess };
    guess_validity is_valid_guess(const std::string &guess) const;

    void apply_guess(const std::string &guess, std::ostream &os = std::cout);

    const std::map<std::string, std::vector<std::string>> &get_last_partition() const;
    const std::string &get_current_hint() const;

    std::string final_word() const;

    friend std::ostream &operator<<(std::ostream &os, const Hangman &h);
private:
    std::string current_hint;
    std::vector<std::string> current_word_list;
    std::string guessed_letters;
    std::map<std::string, std::vector<std::string>> last_partition;
    bool show_cheating;
    int guesses_remaining;
};

std::ostream &operator<<(std::ostream &os, const Hangman &h);

std::string mask_word(const std::string &word, const std::string &guessed_letters);


#endif //INC_01_UNIT_TESTING_HANGMAN_HANGMAN_H
