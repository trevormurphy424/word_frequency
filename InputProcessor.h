#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class InputProcessor{
    public:
        /**
         * @brief Initializes and private data members to sensible values
         * 
         */
        InputProcessor();

        /**
         * @brief Close the file stream.
         * 
         */
        void closeStream();

        /**
         * @brief Returns the private vector of strings
         * 
         * @return vector<string> contains all words of imported file
         */
        vector<string> getAllWords();

        /**
         * @brief Prompt the user for the filename of the file they wish to open, then ope nan input file stream for the given filename
         * 
         * @return true - opened successfully
         */
        bool openStream();

        /**
         * @brief Read all the words that are in the input stream and store in the private vector of all words
         * 
         */
        void read();

    private:
        ifstream _fileIn;
        vector<string> _allWords;
};

#endif