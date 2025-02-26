#include "OutputProcessor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

OutputProcessor::OutputProcessor() {
    _allWords = {};
    _uniqueWords = {};
    _letterCounts = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    _wordCounts = {};
    _totalLetterCount = 0;
    _totalWordCount = 0;
}

bool OutputProcessor::openStream() {
    string filename;
    cout << "Input output file name: ";
    cin >> filename;
    _fileOut.open(filename);

    if(_fileOut.fail()) {
        return false;
    } else {
        return true;
    }
}

void OutputProcessor::analyzeWords(vector<string> wordsList, string punctuation) {
    vector<char> uppercase = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    vector<char> lowercase = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    // Modifies each word
    for(string &word : wordsList) {
        for(size_t i = 0; i < word.length(); i++) {
            
            // Makes each letter uppercase
            for(size_t j = 0; j < lowercase.size(); j++) {
                if(lowercase[j] == word.at(i)){
                    word[i] = uppercase[j];
                }
            }

            // Removes punctuation from words 
            for(size_t j = 0; j < punctuation.length(); j++) {
                if(punctuation[j] == word[i]) {
                    word.erase(i, 1);
                    i -= 1;
                }
            }
        }
        _allWords.push_back(word);
    }

    // Counts characters
    unsigned short int letter;
    for(string &word : _allWords) {
        for(size_t i = 0; i < word.length(); i++) {
            letter = (int)word[i] - 65;
            if(letter <= 25) {
                _letterCounts[letter] += 1;
            }
            _totalLetterCount++;
        }
    }

    // Checks to see if words are in _uniqueWords. if not, adds them.
    bool inList;
    for(const string &word : _allWords) {
        // Checks for presence in list
        inList = false;
        for(size_t i = 0; i < _uniqueWords.size(); i++) {
            if(_uniqueWords[i] == word) {
                _wordCounts[i] += 1;
                inList = true;
            }
        }
        // Adds word and count to respective lists
        if(!inList) {
            _uniqueWords.push_back(word);
            _wordCounts.push_back(1);
        }
    }
}

void OutputProcessor::write() {
    _fileOut << "Read in " << _allWords.size() << " words" << endl;
    _fileOut << "Encountered " << _uniqueWords.size() << " unique words" << endl;

    // variables for most and least frequent words
    string mostFrequent(_uniqueWords[0]), leastFrequent(_uniqueWords[0]);
    double mostFrequentPercent(0), leastFrequentPercent(0);
    unsigned int mostFrequentCount(_wordCounts[0]), leastFrequentCount(_wordCounts[0]), numPlaces;
    unsigned short int count(0);

    // Generate full unique word list
    for(size_t i = 0; i < _uniqueWords.size(); i++) {
        // Check for most frequent words
        if(_wordCounts[i] > mostFrequentCount) {
            mostFrequentCount = _wordCounts[i];
            mostFrequent = _uniqueWords[i];
        } else if (_wordCounts[i] < leastFrequentCount) { // check for least frequent words
            leastFrequentCount = _wordCounts[i];
            leastFrequent = _uniqueWords[i];
        }
    }

    // calculate amount of places in largest word count
    numPlaces = mostFrequentCount; 
    do {
        numPlaces /= 10;
        count++;
    } while(numPlaces >= 1);

    // Get length of the longest word
    unsigned int maxWordLength(1);  // get max word length
    for(const string &word : _uniqueWords) {
        if(word.length() > maxWordLength) {
            maxWordLength = word.length();
        }
    }

    // Print words and their respective counts
    for(size_t i = 0; i < _uniqueWords.size(); i++) {
        _fileOut << left << setw(maxWordLength) << _uniqueWords[i];
        _fileOut << " : " << right << setw(count) << _wordCounts[i] << endl;
    }

    // Calculate the percentages for most and least frequent words
    mostFrequentPercent = (double)mostFrequentCount / (double)_allWords.size() * 100;
    leastFrequentPercent = (double)leastFrequentCount / (double)_allWords.size() * 100; 

    // Check for new longest word (between the most and least frequent words)
    if(mostFrequent.length() > leastFrequent.length()) {
        maxWordLength = mostFrequent.length();
    } else {
        maxWordLength = leastFrequent.length();
    }

    // Print out the most and least frequent words (w/ percentages and counts)
    _fileOut << " Most Frequent Word: " << left << setw(maxWordLength+1) << mostFrequent << right << setw(count) << mostFrequentCount << " (" << setw(7) << fixed << setprecision(3) << mostFrequentPercent << "%)" << endl;
    _fileOut << "Least Frequent Word: " << left << setw(maxWordLength+1) << leastFrequent << right << setw(count) << leastFrequentCount << " (" << setw(7) << fixed << setprecision(3) << leastFrequentPercent << "%)" << endl;


    // Characters:

    // Get largest and smallest character counts
    unsigned int largestNum(_letterCounts[0]), smallestNum(_letterCounts[0]);
    unsigned short int largestIdx, smallestIdx;
    for(size_t i = 0; i < _letterCounts.size(); i++) {
        if(_letterCounts[i] > largestNum) {
            largestIdx = i;
            largestNum = _letterCounts[i];
        } else if(_letterCounts[i] < smallestNum) {
            smallestIdx = i;
            smallestNum = _letterCounts[i];
        }
    }

    // calculate amount of places in largest number of characters
    numPlaces = largestNum;
    count = 0; 
    do {
        numPlaces /= 10;
        count++;
    } while(numPlaces >= 1);

    // Print out letter values
    for(size_t i = 0; i < _letterCounts.size(); i++) {
        _fileOut << char(i+65) << ": " << right << setw(count) << _letterCounts[i] << endl;
    }

    // Calculate letter percentages
    double highLetterPercent, lowLetterPercent;
    highLetterPercent = (double)largestNum / (double)_totalLetterCount * 100;
    lowLetterPercent = (double)smallestNum / (double)_totalLetterCount * 100;

    // Print out most and least frequent letters
    _fileOut << " Most Frequent Letter: " << char(largestIdx+65) << " " << right << setw(count) << _letterCounts[largestIdx] << " (" << setw(7) << fixed << setprecision(3) << highLetterPercent << "%)" << endl;
    _fileOut << "Least Frequent Letter: " << char(smallestIdx+65) << " " << right << setw(count) << _letterCounts[smallestIdx] << " (" << setw(7) << fixed << setprecision(3) << lowLetterPercent << "%)" << endl;
}

void OutputProcessor::closeStream() {
    _fileOut.close();
}


























// :O <- me when this ran after 6 hrs