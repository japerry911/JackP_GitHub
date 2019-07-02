//
// Created by root on 1/26/19.
//

#include "EncodeString.h"
#include <string>
#include <fstream>
#include "StringLetter.h"
#include <iostream>

//Setters and Getters for EncodeString Class (used in testing)
void EncodeString::setPlainTextString(std::string textString) {
    plainTextString = textString;
}

void EncodeString::setCypherTextString(std::string textString) {
    cypherTextString = textString;
}

void EncodeString::setfullKeyString(std::string keyString) {
    fullKeyString = keyString;
}

void EncodeString::setInputtedKey(std::string keyString) {
    inputtedKey = keyString;
}

std::string EncodeString::getCypherStringToDecode() {
    return cypherStringToDecode;
}

std::string EncodeString::getFullKeyString() {
    return fullKeyString;
}

std::string EncodeString::getPlainTextString() {
    return plainTextString;
}

std::string EncodeString::getCypherTextString() {
    return cypherTextString;
}

std::string EncodeString::getInputtedKey() {
    return inputtedKey;
}

std::string EncodeString::getDecodedPlainText() {
    return decodedPlainText;
}

//Get Plain Text String to Encode from File
void EncodeString::getStringFromFile(std::string fileName) {
    std::string ret;

    std::ifstream in(fileName);

    while (!in.eof()) {
        char character = in.get();

        if (in.gcount() != 1) {
            break;
        }

        ret += character;
    }

    in.close();

    plainTextString = ret;
}

//Get Key String from User
void EncodeString::getKeyStringFromUser() {
    std::string cinString;
    bool validationTest = false;

    std::cout << "What would you like for a Key String (Alphabet Characters Only)?" << std::endl;
    std::cin >> cinString;

    //Validate that it is a alphabetical letter
    while (!validationTest) {
        for (int i = 0; cinString.size(); i++) {
            if (!std::isalpha(cinString[i])) {
                break;
            }

            if (i == (cinString.size() - 1)) {
                validationTest = true;
            }
        }

        if (!validationTest) {
            std::cout << "Please enter a valid string." << std::endl;
            std::cin.clear();
            std::cin >> cinString;
        }
    }

    inputtedKey = cinString;
}

//Create a full Key String that matches the plain text string in length
void EncodeString::createFullKeyString() {
    std::string fullString;
    int currentLetter = 0;

    for (int i = 0; i < plainTextString.size(); i++) {
        if (std::isalpha(plainTextString[i])) {
            fullString += inputtedKey[currentLetter];
            currentLetter++;
        } else {
            fullString += plainTextString[i];
        }

        if (currentLetter == inputtedKey.size()) {
            currentLetter = 0;
        }
    }

    fullKeyString = fullString;
}

//Use operator overloaders and convert text letter to cypher code
char EncodeString::convertLetterToCypherCode(StringLetter textLetter, StringLetter keyLetter) {
    StringLetter cypherLetter(StringLetter{textLetter + keyLetter});

    return cypherLetter.stringLetter;
}

//Use operator overloaders and convert cypher code to plain text letter
char EncodeString::convertCypherLetterToPlainText(StringLetter textLetter, StringLetter keyLetter) {
    StringLetter plainTextLetter(StringLetter{textLetter - keyLetter});

    return plainTextLetter.stringLetter;
}

//Encode the Plain Text String into a Cypher String
void EncodeString::encodeCypher(){
    std::string encodedString;

    for (int i = 0; i < plainTextString.size(); i++) {
        StringLetter plainLetter{plainTextString[i]};
        StringLetter keyLetter{fullKeyString[i]};

        char encodedLetter = convertLetterToCypherCode(plainLetter, keyLetter);

        encodedString += encodedLetter;
    }

    cypherTextString = encodedString;

    //Tests
    /*StringLetter testPlainTextLetter = convertLetterToEnumLetter('h');
    StringLetter testKeyLetter = convertLetterToEnumLetter('k');
    StringLetter testStringLetter = convertLetterToCypherCode(testPlainTextLetter, testKeyLetter);

    std::cout << testStringLetter.getLetter(testStringLetter.stringLetter) << std::endl;*/
}

//Grab Cypher String from Temporary File
void EncodeString::grabCypherStringToDecode(std::string fileName) {
    std::string ret;

    std::ifstream in(fileName);

    while (!in.eof()) {
        char character = in.get();

        if (in.gcount() != 1) {
            break;
        }

        ret += character;
    }

    in.close();

    cypherStringToDecode = ret;
}

//Decode the Cypher Text String
void EncodeString::decodeCypher() {
    std::string decodedString;

    for (int i = 0; i < cypherStringToDecode.size(); i++) {
        StringLetter plainLetter{cypherStringToDecode[i]};
        StringLetter keyLetter{fullKeyString[i]};

        char decodedLetter = convertCypherLetterToPlainText(plainLetter, keyLetter);

        decodedString += decodedLetter;
    }

    decodedPlainText = decodedString;
}

//Validate that the plain text string & the cypher text string match
bool EncodeString::validateEncryptAndDecrypt() {
    for (int i = 0; i < plainTextString.size(); i++) {
        if (plainTextString[i] != decodedPlainText[i]) {
            return false;
        }
    }

    return true;
}

//Send the Cypher text to a file
void EncodeString::sendCypherTextToFile(std::string fileName) {
    std::ofstream out(fileName);

    if (!out.is_open()) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    out << cypherTextString;

    out.close();
}
