//Cheating Hangman Assignment 6
//John Jack Perry
//Cyber Programing II

#include <iostream>
#include "Hangman.h"
#include <string>

//Main Function
int main() {
    //Incorrect guess count, make this high for testing, otherwise set to 5 for normal play
    int guess_count = 5;

    //Filename for master wordlist
    std::string filename = "master_wordlist.txt";

    //Declaring Variables
    int length_of_word;
    int game_start_tries = 0;
    bool validation_test;
    bool game_over;
    bool enough_words = false;

    //While loop that runs until the user selects the valid number of characters for a game (runs game within it as well)
    while (!enough_words) {
        //Determines what to output question-wise, in asking for length of word for hangman word
        game_start_tries++;
        if (game_start_tries == 1) {
            std::cout << "What word length do you want? (<1 or non-numeric initiates self-tests)" << std::endl;
        } else {
            std::cout << "Please try again, no words matched that size. Enter a different word length integer." << std::endl;
        }

        //Validation that input for length of word is an int
        std::cin >> length_of_word;
        validation_test = false;
        do {
            if (std::cin.fail() || length_of_word < 1) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter a valid integer greater than 0." << std::endl;
            } else {
                validation_test = true;
            }
        } while ((!validation_test) && !(std::cin >> length_of_word));

        //Initializes Hangman class with length of word
        Hangman game(length_of_word, guess_count);

        //Determines if there are words with the inputted length of word variable
        game.get_word_list_from_file(filename);
        enough_words = game.initial_word_list_filter();

        //Starts the game if there is a valid wordlist with length of words
        if (enough_words) {
            game_over = false;

            //plays game until it returns true and game is over with win or loss
            while (!game_over) {
                game_over = game.play_game();
            }
        }
    }

    return 0;
}