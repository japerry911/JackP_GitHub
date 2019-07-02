//
// Created by root on 1/26/19.
//

#ifndef ASSIGNMENT_3_TRY4_ENCODESTRING_H
#define ASSIGNMENT_3_TRY4_ENCODESTRING_H

#include <string>
#include "StringLetter.h"

class EncodeString {
public:
    void setPlainTextString(std::string textString);
    void setInputtedKey(std::string keyString);
    void setfullKeyString(std::string keyString);
    void setCypherTextString(std::string textString);
    std::string getPlainTextString();
    std::string getInputtedKey();
    std::string getFullKeyString();
    std::string getCypherTextString();
    std::string getDecodedPlainText();
    std::string getCypherStringToDecode();
    void getStringFromFile(std::string fileName);
    void getKeyStringFromUser();
    void createFullKeyString();
    char convertLetterToCypherCode(StringLetter textLetter, StringLetter keyLetter);
    char convertCypherLetterToPlainText(StringLetter textLetter, StringLetter keyLetter);
    void sendCypherTextToFile(std::string fileName);
    void grabCypherStringToDecode(std::string fileName);
    void encodeCypher();
    void decodeCypher();
    bool validateEncryptAndDecrypt();

private:
    std::string plainTextString;
    std::string inputtedKey;
    std::string fullKeyString;
    std::string cypherTextString;
    std::string cypherStringToDecode;
    std::string decodedPlainText;
};


#endif //ASSIGNMENT_3_TRY4_ENCODESTRING_H
