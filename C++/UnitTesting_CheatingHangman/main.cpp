#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "Hangman.h"
#include "WordList.h"

std::vector<std::string> create_word_list(const std::string &filename, int min_pool_size, int max_pool_size);
void game_loop();
bool play_again_prompt();

int main() {
    try {
        do {
            game_loop();
        } while (play_again_prompt());
    } catch (...) {
        std::cout << "Unhandled exception occurred.\n";
    }

    return 0;

}

std::vector<std::string> create_word_list(const std::string &filename, int min_pool_size, int max_pool_size) {
    // Read the whole word list
    std::vector<std::string> full_word_list;
    try {
        full_word_list = read_words_from_file(filename);
    } catch (std::runtime_error &e) {
        std::cout << e.what();
        throw e;

    }

    for (;;) {
        // Prompt for the word length
        std::cout << "What word length would you like? ";
        int length;
        std::cin >> length;

        if (!std::cin.fail()) {
            // Ensure enough words
            std::vector<std::string> filtered = random_sample(filter_words_by_length(full_word_list, length),
                                                              max_pool_size);
            if (filtered.size() >= min_pool_size) {
                return filtered;
            }
            // If here, not enough words
            std::cout << "I'm sorry, there are not enough words of length " << length << "\n";
        } else {
            std::cout << "Invalid input.\n";
        }

        // Clear out std::cin in case they gave us something weird
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    }
}


void game_loop() {
    // Setup game
    int min_pool = 5;
    int max_pool = 10;
    std::vector<std::string> word_list = create_word_list("words.txt", min_pool, max_pool);
    int guesses = 5;
    bool print_details = true;
    Hangman game(word_list, guesses, print_details);

    while (game.status() == Hangman::game_status::not_over) {
        // Print current state
        std::cout << game;

        // Prompt for next guess
        std::string guess;
        for (;;) {
            std::cout << "What letter would you like to guess? ";
            std::cin >> guess;
            auto status = game.is_valid_guess(guess);

            if (status == Hangman::guess_validity::valid) {
                break;
            }
            // Tell them of error
            if (status == Hangman::guess_validity::incorrect_length) {
                std::cout << "Not a valid length\n";
            } else if (status == Hangman::guess_validity::non_letter) {
                std::cout << "That isn't a letter\n";
            } else if (status == Hangman::guess_validity::repeat_guess) {
                std::cout << "You've already made that guess\n";
            }
            // Clear out std::cin in case they gave us something weird
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }

        // Apply guess
        game.apply_guess(guess);
    }
    if (game.status() == Hangman::game_status::win) {
        std::cout << "Congratulations! You win!\n";
    } else {
        std::cout << "I'm sorry, you have lost. The word was " << game.final_word() << "\n";
    }

}

bool play_again_prompt() {
    // Continually prompt if they would like to play again until they enter valid input
    for (;;) {
        // Prompt
        std::cout << "Would you like to play again?  (Y/N) ";

        std::string response;
        std::cin >> response;

        // Check response
        if (response == "y" || response == "Y") {
            return true;
        }
        if (response == "n" || response == "N") {
            return false;
        }

        // Tell them of error
        std::cout << "Unknown input. Try again\n";
        // Clear out std::cin in case they gave us something weird
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    }
}
