#include <iostream>
#include <string>
#include <fstream>
#include "EncodeString.h"
#include "StringLetter.h"

void testFunction();

int main() {
    //Tests ran by testFunction
    //testFunction();

    //Declaring Variables
    std::string fileName = "Assignment3ReadFile.txt";
    std::string tempFileName = "Assignment3TempFile.txt";

    //Declaring encodeStringClass
    EncodeString encodeStringClass;

    //Get the Plain Text String to Encode from File
    encodeStringClass.getStringFromFile(fileName);

    //Get the Key String from the User that has to be alphabetical letters
    encodeStringClass.getKeyStringFromUser();
    //Transform the Key String so that it matches the Plain Text String in length (repeats itself, if necessary)
    encodeStringClass.createFullKeyString();

    //Encode the Plain Text String from File into a Cypher Text String
    encodeStringClass.encodeCypher();
    //Send the newly encoded Cypher Text String to a temp file
    encodeStringClass.sendCypherTextToFile(tempFileName);

    //Output the Encoding of the string (used in QA process)
    std::cout << encodeStringClass.getPlainTextString() << std::endl;
    std::cout << encodeStringClass.getFullKeyString() << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << encodeStringClass.getCypherTextString() << std::endl;
    std::cout << std::endl;

    //Grab the Cypher Text String from a temporary file
    encodeStringClass.grabCypherStringToDecode(tempFileName);
    //Decode the Cypher Text String into a Plain Text String
    encodeStringClass.decodeCypher();

    //Output the Decoding of the string (used in QA process)
    std::cout << encodeStringClass.getCypherStringToDecode() << std::endl;
    std::cout << encodeStringClass.getFullKeyString() << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << encodeStringClass.getDecodedPlainText() << std::endl;

    //Run Validation Test to see if the Plain Text String matches the Decoded String
    bool validationTest = encodeStringClass.validateEncryptAndDecrypt();

    if (!validationTest) {
        std::cout << "Encryption & Decryption do not match!" << std::endl;
    } else {
        std::cout << "Encryption & Decrytion do match!" << std::endl;
    }

    return 0;
}

//Test Function
void testFunction() {
    StringLetter input{'@'};
    StringLetter key{'K'};
    StringLetter expectedValue{'@'};

    //Test Operators using operator overloads
    if ((input + key) != expectedValue) {
        std::cout << "Failed: " << input.stringLetter << " + " << key.stringLetter << ". Actual Result: " << input + key
        << " || Expected Result: " << expectedValue.stringLetter << std::endl;
    } else {
        std::cout << "Succeeded!" << std::endl;
    }
}

