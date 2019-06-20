//
// Created by root on 3/8/19.
//

#ifndef ASSIGNMENT_6_TRY_2_HANGMAN_H
#define ASSIGNMENT_6_TRY_2_HANGMAN_H
#include <vector>
#include <string>
#include <map>

class Hangman {
public:
    explicit Hangman(int size, int guess_count);

    void get_word_list_from_file(std::string filename);
    bool initial_word_list_filter();
    bool play_game();
    bool partitionizer(char guessed_letter);
    bool game_win_check() const;
    bool generate_new_hint(char guessed_letter);
    bool guessed_already_check(char guessed_letter) const;
    std::string return_print_guessed_letters() const;

private:
    int word_length;
    int incorrect_guesses_left;
    std::string current_hint;
    std::map<int, std::vector<std::string>> pre_filtered_list;
    std::vector<std::string> current_list;
    std::vector<char> guessed_letters;
    std::vector<std::string> possible_hints;
    std::map<std::string, std::vector<std::string>> partition_word_map;
};


#endif //ASSIGNMENT_6_TRY_2_HANGMAN_H
