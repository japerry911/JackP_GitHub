//
// Created by root on 3/8/19.
//

#include "Hangman.h"
#include <fstream>
#include <iostream>
#include <string>

//Function to get wordlist from file
void Hangman::get_word_list_from_file(std::string filename) {
    std::string ret;

    std::ifstream in(filename);

    while (!in.eof()) {
        char character = in.get();

        if (in.gcount() != 1) {
            pre_filtered_list[ret.size()].push_back(ret);

            break;
        }

        //Method used to determine if the word is done being pulled since I am pulling char by char
        //If it's a word, push back that word into pre_filtered_list
        if (character == '\n') {
            pre_filtered_list[ret.size()].push_back(ret);
            ret = "";
            continue;
        }

        ret += character;
    }

    in.close();
}

//Initializer for Hangman class
//Modifies the word_length with size, and the incorrect_guesses_left variable to 5
//Also creates the first all blank hint
Hangman::Hangman(int size, int guess_count): word_length(size), incorrect_guesses_left(guess_count) {
    for (int i = 0; i < word_length; i++) {
        current_hint += "_";
    }
}

//Function that creates the first initial word_list
//Also returns true if there are words in the word list (valid length of word), or false if there are none
bool Hangman::initial_word_list_filter() {
    for (const auto &i : pre_filtered_list[word_length]) {
        current_list.push_back(i);
    }

    if (current_list.size() == 0) {
        return false;
    } else {
        std::cout << "There are " << pre_filtered_list[word_length].size() << " words of length " << word_length << std::endl;
        return true;
    }
}

//Main Function for game, runs through rounds where user can guess
//Return true if if the game is over (win or lost), otherwise false so that the forloop in main keeps running
bool Hangman::play_game() {
    std::string starting_output = "The possible words are: ";

    for (const auto &i : current_list) {
        starting_output += i + " ";
    }

    std::cout << starting_output << std::endl;
    std::cout << "There are " << current_list.size() << " words still possible." << std::endl;
    std::cout << "You have " << incorrect_guesses_left << " incorrect guesses left." << std::endl;
    std::cout << "Current hint: " << current_hint << std::endl;
    std::cout << "Guessed letters: " << return_print_guessed_letters() << std::endl;

    char guessed_letter;
    bool guessed_already = false;
    bool is_alpha = false;
    bool result;

    //Inputting guess_letter and validating it to be a letter in alphabet/it hasn't been guessed before
    std::cout << "What letter do you want to guess? ";
    std::cin >> guessed_letter;
    while (!guessed_already || !is_alpha) {
        guessed_already = guessed_already_check(guessed_letter);
        is_alpha = std::isalpha(guessed_letter);

        if (!guessed_already) {
            std::cin.clear();
            std::cout << "'" << guessed_letter << "' has already been guessed. What would you like to guess? ";
            std::cin >> guessed_letter;
        } else if (!is_alpha) {
            std::cin.clear();
            std::cout << "You guessed a non-alphabetic char. What would you like to guess? ";
            std::cin >> guessed_letter;
        }
    }
    std::cout << "You have guessed '" << guessed_letter << "'" << std::endl;
    guessed_letters.push_back(guessed_letter);

    //Sends the guess to the partition tool so user discovers if it's right or wrong guess
    result = partitionizer(guessed_letter);

    if (!result) {
        std::cout << "Unfortunately '" << guessed_letter << "' is not in the word" << std::endl;
    } else {
        std::cout << "You have guessed correctly" << std::endl;
    }

    //Checks if user won the game
    bool game_win = game_win_check();
    if (game_win) {
        std::cout << "You win. The word was " << current_list[0] << std::endl;
        return true;
    }

    if (incorrect_guesses_left == 0) {
        std::cout << "You are out of guesses. You lose." << std::endl;
        return true;
    }

    return false;
}

//Function that returns a string of all of the guessed letters
std::string Hangman::return_print_guessed_letters() const {
    std::string return_string;

    for (const auto &i : guessed_letters) {
        return_string += i;
        return_string += " ";
    }

    return return_string;
}

//Function that handles the partitioning/generates if user is correct or wrong in guess
bool Hangman::partitionizer(char guessed_letter) {
    //Clear map and possible hints to start
    partition_word_map.clear();
    possible_hints.clear();

    //Loop through the current_list that the user had and recreate the partion map / possible hint variables
    for (const auto &i : current_list) {
        std::string temp_hint = current_hint;
        int letter_spot = i.find(guessed_letter);

        if (letter_spot != -1) {
            temp_hint[letter_spot] = guessed_letter;
        }

        partition_word_map[temp_hint].push_back(i);

        if (partition_word_map[temp_hint].size() == 1) {
            possible_hints.push_back(temp_hint);
        }
    }

    //Printing out the partite sets
    std::cout << "The partite sets from your guess are:" << std::endl;
    for (const auto &i : possible_hints) {
        std::cout << i << ": ";
        for (const auto &j : partition_word_map[i]) {
            std::cout << j << ", ";
        }
        std::cout << std::endl;
    }

    //Grabs the new hint for the user, returns true if they have a correct guess otherwise false if incorrect guess
    bool status = generate_new_hint(guessed_letter);

    if (status) {
        return true;
    } else {
        incorrect_guesses_left--;
        return false;
    }
}

//Checks to see if player won game
//Determined based on if there's a dash in the word, if there are none, then user wins and it returns true
bool Hangman::game_win_check() const {
    int underscore_check = current_hint.find("_");

    if (underscore_check == -1) {
        return true;
    } else {
        return false;
    }
}

//Generates the new hint for the player, it sees which possible_hint key in the partition map has the most words
bool Hangman::generate_new_hint(char guessed_letter) {
    int max_size = 0;
    int hint_size = 0;
    std::string top_hint;

    for (int i = 0; i < possible_hints.size(); i++) {
        hint_size = partition_word_map[possible_hints[i]].size();

        if (hint_size > max_size || i == 0) {
            max_size = hint_size;
            top_hint = possible_hints[i];
        }
    }

    current_hint = top_hint;

    //Recreate current_list with the new partition_word_map[current_hint] values
    current_list.clear();
    for (const auto &i : partition_word_map[current_hint]) {
        current_list.push_back(i);
    }

    if (current_hint.find(guessed_letter) != -1) {
        return true;
    } else {
        return false;
    }
}

//Functions that checks if the user guessed the inputted letter already, returns treu if they havent, other returns false
bool Hangman::guessed_already_check(char guessed_letter) const {
    for (const auto &i : guessed_letters) {
        if (guessed_letter == i) {
            return false;
        }
    }

    return true;
}
