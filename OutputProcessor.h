#ifndef OUTPUT_PROCESSOR_H
#define OUTPUT_PROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class OutputProcessor {
    public:
        /**
         * @brief Initializes private data members to sensible values (there are no words present)
         * 
         */
        OutputProcessor();

        /**
         * @brief  For each word in the provided vector, remove all occurrences of all the punctuation characters denoted by the punctuation string and convert each character to its upper case equivalent. Store these modified strings in the appropriate private vector.
         * The function will then compute the unique set of words present in the modified words vector. It will also count the number of occurrences of each unique word in the entire text. The private vectors will be the same size with element positions corresponding to the same word and count.
         * 
         * @param wordsList A vector of strings containing all the words
         * @param punctuation A string denoting punctuation to remove
         */
        void analyzeWords(vector<string> wordsList, string punctuation);

        /**
         * @brief Close the file stream.
         * 
         */
        void closeStream();

        /**
         * @brief Prompt the user for the filename of the fiel tehy wish to open, then open an output file stream for the given filename.
         * 
         * @return true - opened the file successfully
         */
        bool openStream();

        /**
         * @brief This function will print the following information to the output stream, in the order and format specified. This output must match the specification exactly.
         *  1. How many words were read in
         *  2. How many unique words were read in
         *  3. The complete list of unique words and their associated counts
         *  4. The most frequent word
         *  5. The least frequent word
         *  6. A list of letters and their associated counts
         *  7. The most frequent letter
         *  8. The least frequent letter
         * 
         */
        void write();
        
    private:
        ofstream _fileOut;
        vector<string> _allWords;
        vector<string> _uniqueWords;
        vector<unsigned int> _letterCounts;
        vector<unsigned int> _wordCounts;
        unsigned int _totalLetterCount;
        unsigned int _totalWordCount;
};

#endif