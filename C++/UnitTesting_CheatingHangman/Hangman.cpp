//
// Created by Will Mitchell on 2019-03-31.
//

#include "Hangman.h"

#include <random>

Hangman::Hangman(std::vector<std::string> word_list, int guesses, bool show_cheating_)
        : current_hint(
        mask_word(word_list.at(0), "")), // Can create initial mask from first word, regardless of what it is
          current_word_list(std::move(word_list)),
          guessed_letters(),
          last_partition(),
          show_cheating(show_cheating_),
          guesses_remaining(guesses) {
}

Hangman::game_status Hangman::status() const {
    // If out of guesses, it is a loss
    if (guesses_remaining == 0) {
        return Hangman::game_status::loss;
    }

    // If hint matches word, win (this can only match
    // if all letters revealed which also implies no
    // ambiguity left)
    if (current_word_list[0] == current_hint) {
        return Hangman::game_status::win;
    }

    // Otherwise game not yet over
    return Hangman::game_status::not_over;
}

Hangman::guess_validity Hangman::is_valid_guess(const std::string &guess) const {
    // Ensure the size
    if (guess.length() != 1) {
        return Hangman::guess_validity::incorrect_length;
    }

    // Ensure it is a letter
    if (!std::isalpha(guess[0])) {
        return Hangman::guess_validity::non_letter;
    }

    // Ensure it hasn't already been guessed
    if (guessed_letters.find(guess) != std::string::npos) {
        return Hangman::guess_validity::repeat_guess;
    }

    // Haven't found any problems with it, valid
    return Hangman::guess_validity::valid;
}

void Hangman::apply_guess(const std::string &guess, std::ostream &os) {
    guessed_letters += static_cast<char>(std::tolower(guess[0]));

    // Repartition
    last_partition.clear();

    for (const auto & word : current_word_list) {
        last_partition[mask_word(word, guessed_letters)].push_back(word);
    }

    // Find max partite set
    std::string max_mask = last_partition.begin()->first;
    std::vector<std::string>::size_type max_size = last_partition.begin()->second.size();
    for (const auto & pair : last_partition) {
        if (pair.second.size() > max_size) {
            max_mask = pair.first;
            max_size = pair.second.size();
        }
    }

    // Print partite sets if requested
    if (show_cheating) {
        os << "The partite sets from your guess are:\n";
        for (const auto & pair : last_partition) {
            os << pair.first << "(" << pair.second.size() << "): ";
            for (const auto & word : pair.second) {
                os << word << " ";
            }
            os << "\n";
        }
        os << "Maximixed with partition " << max_mask << "\n";
    }

    // Determine if correct
    if (current_hint == max_mask) {
        // Hint has not changed, guess incorrect
        --guesses_remaining;
        os << "I'm sorry, " << guess << " is not part of the word\n";
    } else {
        // Hint has changed, guess correct
        current_hint = max_mask;
        os << "Correct! " << guess << " is part of the word.\n";
    }
    // Update word list
    current_word_list = last_partition[max_mask];
}

const std::map<std::string, std::vector<std::string>> &Hangman::get_last_partition() const {
    return last_partition;
}

const std::string &Hangman::get_current_hint() const {
    return current_hint;
}

std::string Hangman::final_word() const {
    // Pick one of the remaining words to show the game was "legitimate"
    return current_word_list[0];
}

std::ostream &operator<<(std::ostream &os, const Hangman &h) {
    os << "=========\n";
    if (h.show_cheating) {
        os << "The are " << h.current_word_list.size() << " possible words: ";
        for (const auto &word : h.current_word_list) {
            os << word << " ";
        }
        std::cout << "\n";
    }
    os << "You have " << h.guesses_remaining << " incorrect guesses left.\n";
    os << "Current hint: " << h.current_hint << "\n";
    os << "You have guessed: " << h.guessed_letters << "\n";

    return os;
}

std::string mask_word(const std::string &word, const std::string &guessed_letters) {
    std::string masked;

    // Mask word character by character
    for (char c : word) {
        if (guessed_letters.find(c) != std::string::npos) {
            // Have guessed c
            masked += c;
        } else {
            // Have not guessed c
            masked += "_";
        }
    }
    return masked;
}
